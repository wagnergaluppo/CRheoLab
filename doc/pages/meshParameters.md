@page MeshParameter Mesh parameters
@tableofcontents

----


This page is dedicated to the derivation of mesh parameters.

### Face Area
line1

line2

line3


----
### Face Area Vector

For the calculation of the face area vector \f$\vec{S}_f\f$ will utilize the face area (\f$S_f\f$ ) results given in [click on this link](#face-area).

The normal to a surface is defined as a vector which is perpendicular to the surface at a given point. In CFD we are interested in two quantities: the unitary face surface normal \f$\vec{n}_f\f$  and the face area vector\f$\vec{S}_f\f$ . 

Figure X depicts the procedured used to calculate the face unit normal. 

\image html fav_1.svg "Figure 1: Calculation of the face unit normal vector" width=350px 

A vector \f$\vec{v}_3\f$, perpendicular to the face is calculated from the cross-product between the first two consecutive points that compose a face and the face's center of mass. Afterwards, the normal unit vector is calculated by doing the ratio between the vector \f$\vec{v}_3\f$ and its norm. 

The calculation of the surface area vector is finnalized by multiplying the face area with the face normal unit vector.

\image html fav_2.svg "Figure 2: Calculation of the face area vector" width=350px 


By definition the surface unit normal always points outwards from the face. However due to storage requirements, in CRheoLAB as in [OpenFOAM(R)](https://www.openfoam.com/), we will just store the final direction of the face area vector. We will consider \f$\vec{S}_f\f$ to be positive if it points from the owner cell to the neighobour cell, and negative if it points in the other direction.

\image html fav_3.svg "Figure 2: Direction of the face area vector" width=350px 

To this end, the dot product between the vector that connects the center of the owner cell and the neighbour cell \f$\vec{d}_{ON}\f$ and the face area vector. If the operation is positive, \f$\vec{S}_f\f$ is pointing in the correct diction. If the value is negative, \f$\vec{S}_f\f$ is multiplied with a scalar of value -1 to correct its direction.

For more details, please refer to Face::computeAreaVector() .


----
### Face Weighting Factor

The documentation for this topic is adapted from \cite Moukalled2015.

The discretization of the gradient of a property, e.g. \f$\phi\f$ at the cell centroids and faces is fundamental to construct the discretized set of equations for the diffusion and convection terms.

How to do the weighting? Consider the one dimensional ﬁnite volume mesh system shown in Figure FWF1.

\image html linearInterpolation.png "Figure FWF1: Linear Face weighting factor." width=450px

The values of \f$\phi\f$ are known at the control volume centroids \f$C\f$ and \f$F\f$, and are to be used to compute the value of \f$\phi\f$ at the interface \f$f\f$ between these cells.

A simple linear interpolation will result in the following equation:

\f[
	\phi_{f}=g_{f}\phi_{F}+\left(1-g_{f}\right)\phi_{C}
\f]

Where,

\f[
	g_{f}=\frac{\vec{d}_{Cf}}{\vec{d}_{Cf}+\vec{d}_{fF}}
\f]

On the other hand the calculation can be also done by the next equation.

\f[
	\phi_{f}=g_{c}\phi_{C}+\left(1-g_{c}\right)\phi_{F}
\f]

Where,

\f[
	g_{c}=\frac{\vec{d}_{fF}}{\vec{d}_{Cf}+\vec{d}_{fF}}
\f]

The simplicity of this formula does not extend into multi-dimensional situations, as in two or three dimensions, the circumstances become a bit more complicated. In this case, there is not a unique option for the definition of the geometric weighting factors.

One choice would be to base the weighting factor on the respective volumes, such that:

\f[
	g_{f}=\frac{V_{C}}{V_{C}+V_{F}}
\f]

This however yields wrong results in certain cases, as the Figure FWF2 is illustrating.

\image html meshInterpolationsSpecial.png "Figure FWF2: Other mesh types which needs special attention to Face weighting factor." width=650px

A better alternative for such cases, is to base the interpolation on the normal distances to the face \f$f\f$.

Then the interpolation based on the normal distances to the face \f$f\f$ is computed as:

\f[
	g_{f}=\frac{\vec{d}_{Cf}\cdot \vec{e}_{f}}{ \vec{d}_{Cf} \cdot \vec{e}_{f}+ \vec{d}_{fF} \cdot \vec{e}_{f}} ; \vec{e}_{f}=\frac{ \vec{S}_{f}}{\left\| \vec{S}_{f}\right\|}
\f]

where these parameters used for the calculations are presented in Figure FWF3.

\image html generalFaceWeightingFactor.png "Figure FWF3: General Face Weighting Factor parameters." width=750px


In CRheolab we use the same procedure as in [OpenFOAM(R)](https://www.openfoam.com/), which is centered on the Neighbour cell with:

\f[
	g_{c}=\frac{ \left | \vec{d}_{fF} \cdot \vec{S}_f \right | }{ \left | \vec{d}_{Cf} \cdot \vec{S}_f \right | + \left | \vec{d}_{fF} \cdot \vec{S}_f \right |}
\f]

This implementation is carried out in Face::computeWeightingFactor()

@note \f$g_{f} = 1 - g_{C}\f$



----
### Face and Cell Skewness

By definiton the Face Skewness is a measure of the distance between the face center of mass (\f$\vec{F}_{cm}\f$) and the face point that corresponds to the intersection \f$\vec{F}_{i}\f$ of the face and the line that:
* **For Interior Faces**: joins the center of masses of the cells that share the face, owner \f$\vec{O}_{cm}\f$ and neighbour \f$\vec{N}_{cm}\f$;
* **For boundary Faces**: is normal to the face and intersects the boundary (Owner) cell center of mass \f$\vec{O}_{cm}\f$.

This will give the Skewness Vector, \f$\vec{S}_{kw}\f$, (See Figure XX)

\image html FaceIntPt.png "Figure XX: Face Intersection Point and Skewness Vector" width=550px

Then the actual Skewness, \f$S_{kw}\f$, value is obtained by a normalization, as:

\f[
	S_{kw}=\frac{\| \vec{S}_{kw} \|}{M}
\f]

where \f$M\f$ is the maximum magnitude of the following quantities:
* **For Interior Faces**: \f$0.2 \| \vec{O}_{cm} \vec{N}_{cm} \|\f$;
* **For boundary Faces**: \f$0.4 \| \vec{O}_{cm} \vec{F}_{i} \|\f$;
* Projection of the vector that connects the Face center of mass, \f$ \vec{F_{cm}}\f$, with each of the Face Points, \f$\vec{P}_{i}\f$, on the direction of the Skewness Vector, \f$\vec{S}_{kw}\f$, for all the Face Points (see Figure YY). For more details, please refer to Face::computeSkewness()

\image html PtProj.png "Figure YY: Projection of Vector that connects the Face center of mass with the Face Points on the Direction of the Skewness Vector" width=550px

Finnaly the Owner and Neighbour (for interior faces) cells skewness should be updated with the maximum of the value just calculated and the current cell value. This way, the cell skewness will be equal to the maximum skewness of the faces that comprise it. For more details, please refer to Cell::computeSkewness().

