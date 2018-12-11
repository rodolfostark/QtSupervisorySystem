#include "plotter.h"
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QDebug>

Plotter::Plotter(QWidget *parent) : QWidget(parent)
{

}

void Plotter::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QBrush brush;
    QPen pen;

    int indice_menor, indice_maior;
    float y_posterior, y_anterior;

    painter.setRenderHint(QPainter::Antialiasing);

    brush.setColor(QColor(255, 213, 0));
    brush.setStyle(Qt::SolidPattern);

    pen.setColor(QColor(1, 255, 132));
    pen.setWidth(1);

    painter.setBrush(brush);
    painter.setPen(pen);

    painter.drawRect(0,0,width(),height());

    indice_maior = acharMax();
    indice_menor = acharMin();

    pen.setColor(QColor(0, 17, 102));
    pen.setWidth(1);
    painter.setPen(pen);

    for(int i = 1; i<pontos.length()-1; i ++){
        y_posterior = ((float)pontos.at(i)-pontos.at(indice_menor)) / (pontos.at(indice_maior)-pontos.at(indice_menor));
        y_anterior = ((float)pontos.at(i-1)-pontos.at(indice_menor)) / (pontos.at(indice_maior)-pontos.at(indice_menor));
        qDebug() <<"y_posterior = " <<y_posterior<<" e y_anterior = "<<y_anterior;
        painter.drawLine(width()/10*(i-1), y_anterior*height(), width()/10*(i), y_posterior*height());
    }

}



int Plotter::acharMax()
{
    int index = 0;
    for(int i = 1; i<pontos.length()-1; i++){
        if(pontos.at(i) > pontos.at(i-1)){
            index = i;
        }
    }
    return index;
}

int Plotter::acharMin()
{
    int index = 0;
    for(int i = 1; i<pontos.length()-1; i++){
        if(pontos.at(i) < pontos.at(i-1)){
            index = i;
        }
    }
    return index;
}

void Plotter::atualizaPontos(QList<int>  novosPontos)
{
    pontos = novosPontos;
    repaint();
}
