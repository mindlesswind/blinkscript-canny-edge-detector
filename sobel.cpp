kernel sobelintensitymagnitude2D : public ImageComputationKernel<eComponentWise>
{
  Image<eRead, eAccessRanged2D, eEdgeClamped> src;
  Image<eWrite> dst;

param:
  int radius = 1; 
  bool findangle;
  
  

  void define() {
    defineParam(radius, "Radius", 1); 
    defineParam(findangle, "export angle as result", false);
  }

  void init() {
    src.setRange(-radius, -radius, radius, radius);
  };

  void process() {
    float xSobel[3][3] = {
        {47.0f, 0.0f, -47.0f},
        {162.0f, 0.0f, -162.0f},
        {47.0f, 0.0f, -47.0f}
    };

    float ySobel[3][3] = {
        {47.0f, 162.0f, 47.0f},
        {0.0f, 0.0f, 0.0f},
        {-47.0f, -162.0f, -47.0f}
    };

    float xSum;
    float ySum;

    for( int j = -radius; j <= radius; j++)
      for (int i = -radius; i <= radius; i++){
          xSum += src(i, j) * xSobel[i+radius][j+radius];
          ySum += src(i, j) * ySobel[i+radius][j+radius];
      };

    xSum /= 9;
    ySum /= 9;

    float gradient = sqrt(xSum*xSum+ySum*ySum);
    float angle = atan(ySum/xSum);

    if(findangle == false)
      dst() = gradient;
    else
      dst() = angle;
  }
};