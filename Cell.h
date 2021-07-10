#ifndef CELL_H
#define CELL_H

class Face;

class Cell
{
    public:

        // Constructor  
        Cell();

        // Destructor
        virtual  ~Cell(){};

        // Setters
        void setCellFaces(const vector<Face*>& );
        void setCellID(const int& );

        // Getters
        const vector3& getCenterOfMass() const;

        
        // getters and setters for nonOrthogonality attribute
        double getNonOrthogonalityCell();
        void setNonOrthogonalityCell(double);

        vector<Face*> getCellFaces();
        

         
    protected:

    private:

        // cellID
        int ID_;

        // Cell Volume
        double volume_;

        // Cell center of Mass
        vector3 centerOfMass_; 

        // Cell skewness
        double skewness_;

        // Faces that make up a cell
        vector<Face*> cellFaces_;

        // cell non-orthogonality
        double nonOrthogonality_;


};

#endif // CELL_H
