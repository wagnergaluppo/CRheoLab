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

### Face and Cell Skewness

By definiton the Face Skewness is a measure of the distance between the face center of mass (\f$\vec{F_{cm}}\f$) and the face point that corresponds to the intersection \f$\vec{F_{i}}\f$ of the face and the line that:
* **For Interior Faces**: joins the center of masses of the cells that share the face, owner \f$\vec{O_{cm}}\f$ and neighbour \f$\vec{N_{cm}}\f$;
* **For boundary Faces**: is normal to the face and intersects the boundary (Owner) cell center of mass \f$\vec{O_{cm}}\f$.

This will give the Skewness Vector, \f$\vec{S_{kw}}\f$, (See Figure XX)

\image html FaceIntPt.png "Figure XX: Face Intersection Point and Skewness Vector" width=550px

Then the actual Skewness, \f$S_{kw}\f$, value is obtained by a normalization, as:

\f$S_{kw}=\frac{\| \vec{S_{kw}} \|}{M}\f$ 

where \f$M\f$ is the maximum magnitude of the following quantities:
* **For Interior Faces**: \f$0.2 \| \vec{O_{cm} N_{cm}} \|\f$;
* **For boundary Faces**: \f$0.4 \| \vec{O_{cm} F_{i}} \|\f$;
* Projection of the vector that connects the Face center of mass, \f$ \vec{F_{cm}}\f$, with each of the Face Points, \f$\vec{P_{i}}\f$, on the direction of the Skewness Vector, \f$\vec{S_{kw}}\f$, for all the Face Points (see Figure YY).

\image html PtProj.png "Figure YY: Projection of Vector that connects the Face center of mass with the Face Points on the Direction of the Skewness Vector" width=550px

