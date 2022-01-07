// initialize random seed:
srand((unsigned) time(0));

// Generate Random symmTensor Fields
volField<symmTensorField> sTA = randsymmTensorField("sTA", polyMesh, rTime);
volField<symmTensorField> sTB = randsymmTensorField("sTB", polyMesh, rTime);
//compareVolFields<symmTensorField>("Random symmTensor Fields", sTA, sTB);


// Sum Outside the class
volField<symmTensorField> TSum = sTA + sTB;
volField<symmTensorField> TSumOf = offLinesymmTensorFieldSum(sTA,sTB);
//compareVolFields<symmTensorField>("Sum Operation Outside the Class", TSum, TSumOf);


// Sub
volField<symmTensorField> TSub = sTA - sTB;
volField<symmTensorField> TSubOf = offLinesymmTensorFieldSub(sTA,sTB);
//compareVolFields<symmTensorField>("Subtraction Operation Outside the Class", TSub, TSubOf);


// Shift
symmTensor symmTensorShft = randsymmTensor();
volField<symmTensorField> TShfti = sTA + symmTensorShft;
volField<symmTensorField> TShftOf = offLinesymmTensorFieldShft(sTA,symmTensorShft);
sTA.shiftField(symmTensorShft);  
//compareVolFields<symmTensorField>("Shift Operation Outside the Class", TShfti, TShftOf);
//compareVolFields<symmTensorField>("Shift Operation inside the Class", sTA, TShftOf);



// Scale
double scaleFactor = static_cast<double>(rand() % 1000);
volField<symmTensorField> TScaleOf = offLinesymmTensorFieldScale(sTA,scaleFactor);
sTA.scaleField(scaleFactor);   
//compareVolFields<symmTensorField>("Scale Operation", TScaleOf, sTA);


// Vector Field with component of the symmTensor in one direction
vector3 symmTensorProjVec = randVector();
volField<vectorField> projsymmTensorFieldOf = offLinesymmTensorFieldProj(sTA, symmTensorProjVec, polyMesh, rTime);
volField<vectorField> projsymmTensorFieldi =sTA.projectTensorField(symmTensorProjVec);
compareVolFields<vectorField>("Vector Field that is a projection of a symmTensor Field", projsymmTensorFieldOf, projsymmTensorFieldi);


// Scalar Field with the symmTensor Invariants I1
volField<scalarField> symmtensorI1Of = offLinesymmTensorFieldI1(sTA, polyMesh, rTime);
volField<scalarField> symmtensorI1 = sTA.I1ofTensor();
//compareVolFields<scalarField>("Scalar Field with symmTensor Invariant 1", symmtensorI1Of, symmtensorI1);

// Scalar Field with the symmTensor Invariants I2
volField<scalarField> symmtensorI2Of = offLinesymmTensorFieldI2(sTA, polyMesh, rTime);
volField<scalarField> symmtensorI2 = sTA.I2ofTensor();
//compareVolFields<scalarField>("Scalar Field with symmTensor Invariant 2", symmtensorI2Of, symmtensorI2);

// Scalar Field with the symmTensor Invariants I3
volField<scalarField> symmtensorI3Of = offLinesymmTensorFieldI3(sTA, polyMesh, rTime);
volField<scalarField> symmtensorI3 = sTA.I3ofTensor();
compareVolFields<scalarField>("Scalar Field with symmTensor Invariant 3", symmtensorI3Of, symmtensorI3);

