//Warning: connecting a large image to the filter input will cause the kernel to run very slowly!
//If running on a GPU connected to a display, this will cause problems if the time taken to 
//execute the kernel is longer than your operating system allows. Use with caution!
kernel nonmaximusupKernel : public ImageComputationKernel<eComponentWise>
{
    Image<eRead, eAccessRanged2D, eEdgeClamped> intensity;
    Image<eRead, eAccessRanged2D, eEdgeClamped> angle;  
    Image<eWrite> dst;

local:
    int radius;

    void init(){
        radius = 1;
        intensity.setRange(-radius, -radius, radius, radius);
        angle.setRange(-radius, -radius, radius, radius);
  }

    void process() {
        float pixelangle = angle(0, 0);
        float x,y;
        pixelangle *= 180/PI;

        if (pixelangle < 0 )
            pixelangle+=180;
        
        if (pixelangle < 22.5 || pixelangle > 157.5){
            x = intensity(0, 1);
            y = intensity(0, -1);
            } 
        else if (pixelangle >= 22.5 && pixelangle < 67.5){
            x = intensity(1, -1);
            y = intensity(-1, 1);
            }
        else if (pixelangle >= 67.5 && pixelangle < 112.5){
            x = intensity(1, 0);
            y = intensity(-1, 0);
            }
        else if (pixelangle >= 112.5 && pixelangle < 157.5){
            x = intensity(-1, -1);
            y = intensity(1, 1);
            }
        
        if (intensity(0,0) >= x && intensity(0,0) >= y)
            dst() = intensity(0,0);
        else
            dst() = 0;
    }
};