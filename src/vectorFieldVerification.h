    
    //volField<vectorField> UA ("U", polyMesh, time, MUST_READ);
    //volField<vectorField> UB ("U", polyMesh, time, MUST_READ);
    //volField<vectorField> UC = UA + UB;
    //volField<vectorField> UD = UA - UB;

//volField<vectorField> UA ("UA",polyMesh,time,NO_READ);
//volField<vectorField> UB ("UB",polyMesh,time,NO_READ);



// initialize random seed:
srand((unsigned) time(0));

// Generate Random Vector Fields
volField<vectorField> UA = randVectorField("UA", polyMesh, rTime);
volField<vectorField> UB = randVectorField("UB", polyMesh, rTime);
compareVolFields<vectorField>("Random Vector Fields", UA, UB);

// Sum Outside the class
volField<vectorField> USum = UA + UB;
volField<vectorField> USumOf = offLineVectorFieldSum(UA,UB);
compareVolFields<vectorField>("Sum Operation Outside the Class", USum, USumOf);

// Sub
volField<vectorField> USub = UA - UB;
volField<vectorField> USubOf = offLineVectorFieldSub(UA,UB);
compareVolFields<vectorField>("Subtraction Operation Outside the Class", USub, USubOf);

// Shift
vector3 vectShft = randVector();
volField<vectorField> UShfti = UA + vectShft;
volField<vectorField> UShftOf = offLineVectorFieldShft(UA,vectShft);
UA.shiftField(vectShft);
compareVolFields<vectorField>("Shift Operation Outside the Class", UShfti, UShftOf);
compareVolFields<vectorField>("Shift Operation inside the Class", UA, UShftOf);

// Scale
double scaleFactor = static_cast<double>(rand() % 1000);
volField<vectorField> UScaleOf = offLineVectorFieldScale(UA,scaleFactor);
UA.scaleField(scaleFactor);
compareVolFields<vectorField>("Scale Operation", UScaleOf, UA);

// Scalar Field for the magnitude of a Vector
volField<scalarField> magVectorFieldOf = offLineVectorFieldMag(UA, polyMesh, rTime);
volField<scalarField> magVectorField = UA.magVector();
compareVolFields<scalarField>("Scalar Field with the Magnitude Of Vector Field", magVectorFieldOf, magVectorField);


// Vector Field for the project of a vector in one Direction
vector3 vectProj = randVector(); //{1, 0, 0};//randVector();
volField<vectorField> projVectorFieldOf = offLineVectorFieldProj(UA, vectProj);
UA.projectVectorField(vectProj);
compareVolFields<vectorField>("Vector Field that is a projection of a Vector Field", projVectorFieldOf, UA);


//volField<vectorField> USum = UA + UB;
//volField<vectorField> USum2 = offLineSum(UA,UB);

