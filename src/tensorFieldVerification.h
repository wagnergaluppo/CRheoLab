// initialize random seed:
srand((unsigned) time(0));

// Generate Random Tensor Fields
volField<tensorField> TA = randTensorField("TA", polyMesh, rTime);
volField<tensorField> TB = randTensorField("TB", polyMesh, rTime);
compareVolFields<tensorField>("Random Tensor Fields", TA, TB);


// Sum Outside the class
volField<tensorField> TSum = TA + TB;
volField<tensorField> TSumOf = offLineTensorFieldSum(TA,TB);
compareVolFields<tensorField>("Sum Operation Outside the Class", TSum, TSumOf);


// Sub
volField<tensorField> TSub = TA - TB;
volField<tensorField> TSubOf = offLineTensorFieldSub(TA,TB);
compareVolFields<tensorField>("Subtraction Operation Outside the Class", TSub, TSubOf);


// Shift
tensor tensorShft = randTensor();
volField<tensorField> TShfti = TA + tensorShft;
volField<tensorField> TShftOf = offLineTensorFieldShft(TA,tensorShft);
TA.shiftField(tensorShft);  
compareVolFields<tensorField>("Shift Operation Outside the Class", TShfti, TShftOf);
compareVolFields<tensorField>("Shift Operation inside the Class", TA, TShftOf);



// Scale
double scaleFactor = static_cast<double>(rand() % 1000);
volField<tensorField> TScaleOf = offLineTensorFieldScale(TA,scaleFactor);
TA.scaleField(scaleFactor);   
compareVolFields<tensorField>("Scale Operation", TScaleOf, TA);


// Vector Field with component of the tensor in one direction
vector3 tensorProjVec = randVector();
volField<vectorField> projTensorFieldOf = offLineTensorFieldProj(TA, tensorProjVec, polyMesh, rTime);
volField<vectorField> projTensorFieldi = TA.projectTensorField(tensorProjVec);
compareVolFields<vectorField>("Vector Field that is a projection of a Tensor Field", projTensorFieldOf, projTensorFieldi);


// Scalar Field with the Tensor Invariants I1
volField<scalarField> tensorI1Of = offLineTensorFieldI1(TA, polyMesh, rTime);
volField<scalarField> tensorI1 = TA.I1ofTensor();
compareVolFields<scalarField>("Scalar Field with Tensor Invariant 1", tensorI1Of, tensorI1);

// Scalar Field with the Tensor Invariants I2
volField<scalarField> tensorI2Of = offLineTensorFieldI2(TA, polyMesh, rTime);
volField<scalarField> tensorI2 = TA.I2ofTensor();
compareVolFields<scalarField>("Scalar Field with Tensor Invariant 2", tensorI2Of, tensorI2);

// Scalar Field with the Tensor Invariants I3
volField<scalarField> tensorI3Of = offLineTensorFieldI3(TA, polyMesh, rTime);
volField<scalarField> tensorI3 = TA.I3ofTensor();
compareVolFields<scalarField>("Scalar Field with Tensor Invariant 3", tensorI3Of, tensorI3);

