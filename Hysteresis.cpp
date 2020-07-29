kernel hysteresisKernel : public ImageComputationKernel<eComponentWise>
{
    Image<eRead, eAccessRanged2D, eEdgeClamped> src;
    Image<eWrite> dst;


param:
    float highthres;
    float lowthres;
    float strongpixel;
    float weakpixel;
    float nonrel;

local:
    int radius;

    void define() {
        defineParam(strongpixel, "Strong pixels value", 1.0f);
        defineParam(weakpixel, "Weak pixels value", 0.1f);
        defineParam(nonrel, "non-relevant pixels value ", 0.0f);
    }



    void init(){
        radius = 1;
        src.setRange(-radius, -radius, radius, radius);
    }

    void process() {

        bool strongnel = false;

        if (src(0,0) != weakpixel){
            dst() = src(0,0);
            return;
            };

        for( int j = -radius; j <= radius; j++)
            for (int i = -radius; i <= radius; i++){
                if (src(i,j) == strongpixel){
                    strongnel=true;
                    break;
                };
            };
        
        if (strongnel == true)
            dst() = strongpixel;
        else
            dst() = nonrel;

    };
};