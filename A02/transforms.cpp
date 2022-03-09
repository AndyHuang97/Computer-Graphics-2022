	// Translate of +2 on the x axis, and -1 on the y axis
	float trX = 2.0;
	float trY = -1.0;
	float trZ = 0.0;
	const float MT1[] =  {
			   1.0,		0.0,		0.0,		trX,
			   0.0,		1.0,		0.0,		trY,
			   0.0,		0.0,		1.0,		trZ,
			   0.0,		0.0,		0.0,		1.0};
			   
	// Rotate of 45 degrees on the x axis
	float angle = M_PI/4;
	float rtYY = std::cos(angle);
	float rtYZ = - std::sin(angle);
	float rtZY = std::sin(angle);
	float rtZZ = std::cos(angle);
	const float MT2[] =  {
			   1.0,		0.0,		0.0,		0.0,
			   0.0,		rtYY,		rtYZ,		0.0,
			   0.0,		rtZY,		rtZZ,		0.0,
			   0.0,		0.0,		0.0,		1.0};
			   
	// Make the object 2 times smaller
	float s = 0.5;
	const float MT3[] =  {
			     s,		0.0,		0.0,		0.0,
			   0.0,		  s,		0.0,		0.0,
			   0.0,		0.0,		  s,		0.0,
			   0.0,		0.0,		0.0,		1.0};
			   
	// Make the object 2 times longer on the z axis, and half on the other axis
	float sX = 0.5;
	float sY = 0.5;
	float sZ = 2.0;
	const float MT4[] =  {
			    sX,		0.0,		0.0,		0.0,
			   0.0,		 sY,		0.0,		0.0,
			   0.0,		0.0,		 sZ,		0.0,
			   0.0,		0.0,		0.0,		1.0};

	// Mirror over the z axis
	float mX = -1;
	float mY = -1;
	float mZ = 1;
	const float MT5[] =  {
			    mX,		0.0,		0.0,		0.0,
			   0.0,		 mY,		0.0,		0.0,
			   0.0,		0.0,		 mZ,		0.0,
			   0.0,		0.0,		0.0,		1.0};
			   
	// Flatten over the z axis
	float fX = 1.0;
	float fY = 1.0;
	float fZ = 0.0;
	const float MT6[] =  {
			    fX,		0.0,		0.0,		0.0,
			   0.0,		 fY,		0.0,		0.0,
			   0.0,		0.0,		 fZ,		0.0,
			   0.0,		0.0,		0.0,		1.0};

	// Make a shear along the Y axis, with a factor of 1 along the x axis
	float hX = 1.0;
	float hZ = 0.0;
	const float MT7[] =  {
			   1.0,		 hX,		0.0,		0.0,
			   0.0,		1.0,		0.0,		0.0,
			   0.0,		 hZ,		1.0,		0.0,
			   0.0,		0.0,		0.0,		1.0};
