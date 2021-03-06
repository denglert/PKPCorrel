#include "TGraphErrors.h"
// charged hadron results
// Panel5, pPb, v22, 120 < N < 150
//
 
TGraphErrors CMSres_v2_chadron_nTrkdep() 
{

int numpoints = 18;

double nTrk[] = {
6.917,
14.37,
24.41,
34.39,
44.36,
54.33,
68.63,
88.39,
108.2,
131.3,
162.1,
196.6,
227.5,
247.2,
267.1,
287.0,  
306.8,
328.6
};

double v2[] = {
0.05367,
0.05428,
0.05379,
0.05501,
0.05651,
0.05814,
0.06038,
0.0629 ,
0.06421,
0.06633,
0.06777,
0.06887,
0.06927,
0.0697 ,
0.06977,
0.06896,
0.06706,
0.06621,
};

double nTrkerr[] = {
0.001655 ,
0.0006222,
0.0003994,
0.0002977,
0.0002436,
0.0002135,
0.0001381,
0.0001397,
0.0001624,
4.268e-05,
3.212e-05,
2.831e-05,
4.645e-05,
8.416e-05,
0.0001636,
0.0003366,
0.000741 ,
0.00147
};

double v2err[] = {
0.002093,
0.002117,
0.002098,
0.002145,
0.002204,
0.002267,
0.002355,
0.002453,
0.002504,
0.002587,
0.002643,
0.002686,
0.00381 ,
0.003833,
0.005163,
0.005103,
0.004962,
0.0049
};

TGraphErrors graph = TGraphErrors(numpoints, nTrk, v2, nTrkerr, v2err);
return graph;

}


TGraphErrors CMSres_v2_chadron_120_150() 
{
	int numpoints = 9;
	
	double pt[] = {
	0.40,
	0.75,
	1.25,
	1.75,
	2.25,
	2.75,
	3.40,
	4.40,
	5.40
	};
	
	double v2[] = {
	0.03421,
	0.05947,
	0.09341,
	0.11930,
	0.13850,
	0.14980,
	0.16120,
	0.16220,
	0.16360
	};
	
	double pterr[] = {
	7.6e-05,
	6.9e-05,
	0.00011,
	0.00016,
	0.00025,
	0.00036,
	0.00042,
	0.00070,
	0.00110
	};
	
	double v2err[] = {
	0.0013,
	0.0023,
	0.0036,
	0.0047,
	0.0054,
	0.0058,
	0.0063,
	0.0063,
	0.0064
	};

	TGraphErrors graph = TGraphErrors(numpoints, pt, v2, pterr, v2err);
	return graph;

}

TGraphErrors CMSres_v2_chadron_150_185() 
{

	int numpoints = 9;
	
	double pt[] = {
	0.40,
	0.75,
	1.25,
	1.75,
	2.25,
	2.75,
	3.40,
	4.40,
	5.40
	};
	
	double v2[] = {
	0.03509,
	0.06061,
	0.09421,
	0.12   ,
	0.1395 ,
	0.1511 ,
	0.1591 ,
	0.1589 ,
	0.1547 ,
	};
	
	double pterr[] = {
	0.0,
	0.0,
	0.0,
	0.0,
	0.0,
	0.0,
	0.0,
	0.0,
	0.0
	};
	
	double v2err[] = {
	6.6e-05,
	5.7e-05,
	8.9e-05,
	0.00013,
	0.00021,
	0.00031,
	0.00035,
	0.0006 ,
	0.00097
	};
	
	TGraphErrors graph = TGraphErrors(numpoints, pt, v2, pterr, v2err);
	return graph;

}

TGraphErrors CMSres_v2_chadron_185_220() 
{

	int numpoints = 9;

	double pt[] = {
	0.40,
	0.75,
	1.25,
	1.75,
	2.25,
	2.75,
	3.40,
	4.40,
	5.40
	};
	
	double v2[] = {
	0.03578,
	0.06115,
	0.09462,
	0.1205 ,
	0.1393 ,
	0.1505 ,
	0.1575 ,
	0.1559 ,
	0.1492 ,
	};
	
	double pterr[] = {
	0.0,
	0.0,
	0.0,
	0.0,
	0.0,
	0.0,
	0.0,
	0.0,
	0.0
	};
	
	double v2err[] = {
	 5.8e-05,
	 5e-05  ,
	 7.8e-05,
	0.00012 ,
	0.00017 ,
	0.00026 ,
	0.00031 ,
	0.00052 ,
	0.00084 
	};
	
	TGraphErrors graph = TGraphErrors(numpoints, pt, v2, pterr, v2err);
	return graph;

}
