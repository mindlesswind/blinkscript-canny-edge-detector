kernel Gaussian2D : public ImageComputationKernel<eComponentWise>
{
  Image<eRead, eAccessRanged2D, eEdgeClamped> src;
  Image<eWrite> dst;

param:
  int Radius;  
  float sigma;
  
  void define() {
    defineParam(Radius, "Radius", 30); 
    defineParam(sigma, "Sigma", 50.0f); 
  }

  void init() {
    src.setRange(-Radius, -Radius, Radius, Radius);
  }

  void process() {
    float _weightSum = 0.0f;
    float _sum = 0.0f;
    float _gaussfactor;

    

    for (int j = -Radius; j <= Radius; j++)
      for (int i = -Radius; i <= Radius; i++){
        _gaussfactor = 1/(2*PI*sigma*sigma)*exp(-(i*i+j*j)/(2*sigma*sigma));
        _sum += src(i, j) * _gaussfactor;
        _weightSum += _gaussfactor;
      };
        
    dst() = _sum / _weightSum;
  }
};