#ifndef Velocity_h
#define Velocity_h

class Velocity
{
private:

    float dx;
    float dy;

public:

    Velocity();
    Velocity(float dx, float dy);

    //Accessors and  Mutators
    float getdx() const;
    float getdy() const;
    void setdx(float dx);
    void setdy(float dy);

};

#endif /* Velocity_h */
