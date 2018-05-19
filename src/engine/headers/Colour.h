#ifndef __COLOUR_H__
#define __COLOUR_H__

class Colour{

	float r;
	float g;
	float b;

	public:
		Colour();
		Colour(float,float,float);
		float getR();
		float getG();
		float getB();
		void setR(float);
		void setG(float);
		void setB(float);
		Colour* clone();
		virtual ~Colour();

};

#endif
