kernel deSatuation2D : public ImageComputationKernel<ePixelWise>
{

  //different than default blink kernal, this version is write on eAccessRanged2D for trainning

  Image<eRead, eAccessRanged2D, eEdgeClamped> src;
  Image<eWrite, eAccessPoint> dst;

local:
  float3 coefficients;

  void init() {

    coefficients.x = 0.2126f;
    coefficients.y = 0.7152f;
    coefficients.z = 0.0722f;

    src.setRange(-src.bounds.width()/2, -src.bounds.height()/2, 
                src.bounds.width()/2, src.bounds.height()/2);
  }
  
  void process() {

    float4 input = src(0, 0);
    float3 luma = rgb_to_grey(input);

    dst() = float4(luma.x, luma.y, luma.z, src(0,0,3));  //src(0,0,3) = the forth channel (rgb[a])
  }

  float3 rgb_to_grey(float4 input){
    float luma = input.x * coefficients.x
        + input.y * coefficients.y
        + input.z * coefficients.z;
    return luma;
  }
};