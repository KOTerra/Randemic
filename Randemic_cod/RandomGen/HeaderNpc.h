#include "OmClass.h"

static const int razaShape = 10;//raza omului
static const float speed = 25;//viteza cu care merge

std::string getSex(bool sexbool);

std::string getNextPrenume(bool sexbool, std::string prenPrec);

std::string getPrenume(bool sexbool);

void getNume(std::string prenume);

int getVarsta();

std::string getInaltime(int varsta, bool sexbool);

std::string getSociabilitate(int inaltime, int varsta);


std::map<std::string, OmClass> simulare(int NrNpc);