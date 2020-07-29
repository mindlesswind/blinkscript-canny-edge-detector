kernel doublethresholdKernel : public ImageComputationKernel<eComponentWise>
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
        defineParam(highthres, "High threshold", 20.0f); 
        defineParam(lowthres, "Low threshold", 5.0f);
        defineParam(strongpixel, "Strong pixels value", 1.0f);
        defineParam(weakpixel, "Weak pixels value", 0.1f);
        defineParam(nonrel, "non-relevant pixels value ", 0.0f);
    }



    void init(){
    }

    void process() {
        if (src(0,0) >= highthres)
            dst() = strongpixel;
        else if (src(0,0) < lowthres)
            dst() = nonrel;
        else
            dst() = weakpixel;
    };
};