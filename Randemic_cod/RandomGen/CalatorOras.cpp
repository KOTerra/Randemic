#include "CalatorOras.h"


CalatorOras::CalatorOras(float pX,float pY, sf::Vector2f directie, std::map<std::string, Oras>::iterator tinta)
{
	this->pX = pX;
	this->pY = pY;
	this->misc = directie;
	this->tinta = tinta;

	this->shape.setRadius(razaShape);
	this->shape.setOutlineColor(sf::Color(0, 0, 0));
	this->shape.setFillColor(sf::Color(100, 255, 0));
	this->shape.setOutlineThickness(1);
	this->shape.setPosition(pX,pY);
}

bool CalatorOras::isTouchingOras(int R, int X1, int Y1, int X2, int Y2) {

	int Xc = this->pX;
	int Yc = this->pY;

    // Find the nearest point on the
   // rectangle to the center of
   // the circle
    int Xn = std::max(X1, std::min(Xc, X2));
    int Yn = std::max(Y1, std::min(Yc, Y2));

    // Find the distance between the
    // nearest point and the center
    // of the circle
    // Distance between 2 points,
    // (x1, y1) & (x2, y2) in
    // 2D Euclidean space is
    // ((x1-x2)**2 + (y1-y2)**2)**0.5
    int Dx = Xn - Xc;
    int Dy = Yn - Yc;
    return (Dx * Dx + Dy * Dy) <= R * R;
}
void CalatorOras::move(float dt)
{
    sf::Vector2f vec1 = this->misc;
    vec1.x = vec1.x * dt;
    vec1.y = vec1.y * dt;

    this->shape.move(vec1);

    auto pozitie = this->shape.getPosition();
    this->pX= pozitie.x + razaShape;
    this->pY = pozitie.y + razaShape;
}