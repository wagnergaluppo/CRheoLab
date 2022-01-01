// initialize random seed:
srand((unsigned) time(0));

// Generate Random Vector Fields
volField<scalarField> sA = randScalarField("sA", polyMesh, rTime);
volField<scalarField> sB = randScalarField("sB", polyMesh, rTime);
compareVolFields<scalarField>("Random Scalar Fields", sA, sB);

// Sum Outside the class
volField<scalarField> sSum = sA + sB;
volField<scalarField> sSumOf = offLineScalarFieldSum(sA,sB);
compareVolFields<scalarField>("Sum Operation Outside the Class", sSum, sSumOf);


// Sub
volField<scalarField> sSub = sA - sB;
volField<scalarField> sSubOf = offLineScalarFieldSub(sA,sB);
compareVolFields<scalarField>("Subtraction Operation Outside the Class", sSub, sSubOf);


// Shift
double scalarShft = randScalar();
volField<scalarField> sShfti = sA + scalarShft;
volField<scalarField> sShftOf = offLineScalarFieldShft(sA,scalarShft);
sA.shiftField(scalarShft);
compareVolFields<scalarField>("Shift Operation Outside the Class", sShfti, sShftOf);
compareVolFields<scalarField>("Shift Operation inside the Class", sA, sShftOf);

// Scale
double scaleFactor = static_cast<double>(rand() % 1000);
volField<scalarField> sScaleOf = offLineScalarFieldScale(sA,scaleFactor);
sA.scaleField(scaleFactor);
compareVolFields<scalarField>("Scale Operation", sScaleOf, sA);

