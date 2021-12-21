    
    volField<vectorField> UA ("U", polyMesh, time, MUST_READ);
    volField<vectorField> UB ("U", polyMesh, time, MUST_READ);
    volField<vectorField> UC = UA + UB;
    volField<vectorField> UD = UA - UB;

    volField<scalarField> magVec = UA.magVector();
    //UC.shiftField(UA.internalField());
    //UC.shiftMinField(UA.internalField());
    //UC.shiftMaxField(UA.internalField());