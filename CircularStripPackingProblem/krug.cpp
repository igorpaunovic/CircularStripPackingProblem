#include "krug.h"
#include "tomsolver.h"

Krug::Krug(const QPoint& centar, int poluprecnik, const QColor& boja, QWidget *pCrtanja)
    : _centar(centar), _poluprecnik(poluprecnik), _boja(boja), _pCrtanja(pCrtanja)
{};

void Krug::crtaj(QPainter *painter) const {
    painter->setPen(Qt::blue);
    painter->setBrush(_boja);
    painter->drawEllipse(_centar, _poluprecnik, _poluprecnik);
}

void Krug::pomeri(QPoint noviCentar) {
    _centar = noviCentar;
    _boja = Qt::red;
}

int Krug::gore() const {
    return _centar.y() + _poluprecnik;
};

int Krug::dole() const {
    return _centar.y() - _poluprecnik;
};

int Krug::levo() const {
    return _centar.x() - _poluprecnik;
};

int Krug::desno() const {
    return _centar.x() + _poluprecnik;
};

bool Krug::neSeceKrug(Krug& krug) const {
    int udaljenostX = (_centar.x() - krug._centar.x());
    int udaljenostY = (_centar.y() - krug._centar.y());
    return (_poluprecnik + krug._poluprecnik <= int(qSqrt(udaljenostX*udaljenostX + udaljenostY*udaljenostY)));
};

bool Krug::neSeceKrugove(std::set<Krug*>& krugovi) const {
    for (const auto &krug : krugovi) {
        if (!neSeceKrug(*krug)) {
            return false;
        }
    }
    return true;
};

std::vector<QPoint*> Krug::ugaoIzmedjuDvaKruga(const Krug &krug1, const Krug &krug2) const {
    double x1 = krug1._centar.x(), y1 = krug1._centar.y(), r1 = krug1._poluprecnik;
    double x2 = krug2._centar.x(), y2 = krug2._centar.y(), r2 = krug2._poluprecnik;
    double r3 = _poluprecnik;

    double d1 = r1 + r3;
    double d2 = r2 + r3;

    std::vector<QPoint*> uglovi;

    // Slucaj kad je krug dovoljno mali pa ne dodiruje oba kruga istovremeno
    if (r1 + r2 + 2*r3 < int(qSqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2)))) {
        return uglovi;
    }

    // Slucaj kad su krugovi 1 i 2 isti krug - verovatno se nece ni dogoditi
    if (x1 == x2 and y1 == y2) {
        return uglovi;
    }

    try {
        // create equations as a symbolic vector
        tomsolver::SymVec f{
            tomsolver::Parse("(x-x1)^2 + (y-y1)^2 - d1^2"),
            tomsolver::Parse("(x-x2)^2 + (y-y2)^2 - d2^2")
        };

        // replace known values
        f.Subs(tomsolver::VarsTable{
            {"x1", x1},
            {"y1", y1},
            {"x2", x2},
            {"y2", y2},
            {"d1", d1},
            {"d2", d2},
        });

        std::cout << f << std::endl;

        // solve
        auto ans = Solve(f);

        double x = int(ans["x"]);
        double y = int(ans["y"]);

        // Ovo je samo jedno resenje, treba da nadjemo refleksiju po liniji koja prolazi kroz centre oba kruga za drugo resenje
        double A, B, C;
        if (x1 == x2) { // Vertical line case
            A = 1;
            B = 0;
            C = -x1;
        } else if (y1 == y2) { // Horizontal line case
            A = 0;
            B = 1;
            C = -y1;
        } else {
            // Compute coefficients for non-vertical, non-horizontal lines
            A = y2 - y1;
            B = x1 - x2;
            C = x2 * y1 - x1 * y2;
        }

        // Calculate the perpendicular projection of (x1, y1) on the line
        double denom = A * A + B * B;
        double xProjekcija = (B * (B * x - A * y) - A * C) / denom;
        double yProjekcija = (A * (-B * x + A * y) - B * C) / denom;

        // Calculate the mirror point
        int xMirror = 2 * xProjekcija - x;
        int yMirror = 2 * yProjekcija - y;

        uglovi.push_back(new QPoint(int(x), int(y)));
        uglovi.push_back(new QPoint(int(xMirror), int(yMirror)));

        return uglovi;
    } catch (const std::exception &err) {
        qDebug() << "Ne postoji takav krug";
        return uglovi;
    }
};
