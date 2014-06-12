/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "glwidget.h"
#include <QMouseEvent>
#include <QWheelEvent>
#include <QDebug>
#include <QString>

QString gPath;

void GlWidget::setPath(const QString &mPath)
{
    gPath = mPath;
}

GlWidget::GlWidget(QWidget *parent)
    : QGLWidget(QGLFormat(/* Additional format options */), parent)
{
    alpha = 25;
    beta = -25;
    distance = 1;
}

GlWidget::~GlWidget()
{
}

QSize GlWidget::sizeHint() const
{
    return QSize(640, 480);
}

//! [0]
void GlWidget::initializeGL()
{
    //! [0]
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    int nVertices;

    //Open and parse file
    QString mPath = gPath;
    QString SearchString = "outer loop";
    QFile mFile(mPath);
    mFile.open(QFile::ReadOnly | QFile::Text);
    QTextStream in(&mFile);
    QString mFileContents = in.readAll();
    nVertices = mFileContents.count(SearchString); //Set number of vertices
    mFile.close();
    /*************************************************/

    //declare x, y, z arrays with vertex count
    const int nn = nVertices * 3;
    const int nnn = nVertices;
    int *x = new int[nn];
    int *y= new int[nn];
    int *z = new int[nn];
//    int *xNormals = new int[nnn];
//    int *yNormals = new int[nnn];
//    int *zNormals = new int[nnn];
//    int nVertexIndex = 0;
    max_x = 0;
    max_y = 0;
    max_z = 0;
    min_x = 0;
    min_y = 0;
    min_z = 0;
    /*************************************************/

    //grab x, y, and z coordinates.
    QStringList mList;
    QStringList mList2;
    QStringList fList;
    QStringList ffList;
//    QStringList nList;
//    QStringList nnList;
    int sIndex = 0;
    int nVertexIndex;

    mList = mFileContents.split(QRegExp("\n"));
    mList2 = mList;

    for (int index = 0; index < mList.size(); index++)
    {
        if(mList[index].contains("vertex") == true)
        {
            fList << mList[index];
        }
    }

    for (int index = 0; index < fList.size(); index++)
    {
        QStringList tList;
        tList = fList[index].split(QRegExp("\\s+"),QString::SkipEmptyParts);
        for (int subindex = 0; subindex < tList.size(); subindex++)
        {
            if((tList[subindex].contains("vertex") == 0))
            {
                ffList << tList[subindex];
            }
        }
    }

    for (int index = 0; index < (nVertices*3); index++)
    {
        x[index] = ffList[sIndex].toDouble();
        if (ffList[sIndex].toDouble() > distance)
        {
            distance = ffList[sIndex].toDouble();
        }
        if (ffList[sIndex].toDouble() > max_x)
        {
            max_x = ffList[sIndex].toDouble();
        }
        if (ffList[sIndex].toDouble() < min_x)
        {
            min_x = ffList[sIndex].toDouble();
        }
        sIndex++;

        y[index] = ffList[sIndex].toDouble();
        if (ffList[sIndex].toDouble() > distance)
        {
            distance = ffList[sIndex].toDouble();
        }
        if (ffList[sIndex].toDouble() > max_y)
        {
            max_y = ffList[sIndex].toDouble();
        }
        if (ffList[sIndex].toDouble() < min_y)
        {
            min_y = ffList[sIndex].toDouble();
        }
        sIndex++;

        z[index] = ffList[sIndex].toDouble();
        if (ffList[sIndex].toDouble() > distance)
        {
            distance = ffList[sIndex].toDouble();
        }
        if (ffList[sIndex].toDouble() > max_z)
        {
            max_z = ffList[sIndex].toDouble();
        }
        if (ffList[sIndex].toDouble() > min_z)
        {
            min_z = ffList[sIndex].toDouble();
        }
        sIndex++;
    }

    distance = distance * 5;
    max_x = (max_x + min_x)/ 2;
    max_y = (max_y + min_y) / 2;
    max_z = (max_z + min_z)/ 2;

    /*************************************************/

//    //Grab Normals

//    for (int index = 0; index < mList2.size(); index++)
//    {
//        if(mList2[index].contains("facet normal") == true)
//        {
//            nList << mList2[index];
//        }
//    }

//    for (int index = 0; index < nList.size(); index++)
//    {
//        QStringList tList;
//        tList = nList[index].split(QRegExp("\\s+"),QString::SkipEmptyParts);
//        for (int subindex = 0; subindex < tList.size(); subindex++)
//        {
//            if((tList[subindex].contains("facet") == 0) && (tList[subindex].contains("normal") == 0))
//            {
//                nnList << tList[subindex];
//            }
//        }
//    }

//    sIndex = 0;

//    for (int index = 0; index < (nVertices*3); index++)
//    {
//        xNormals[index] = nnList[sIndex].toDouble();
//        sIndex++;

//        yNormals[index] = nnList[sIndex].toDouble();
//        sIndex++;

//        zNormals[index] = nnList[sIndex].toDouble();
//        sIndex++;
//    }
//    /************************************************/

    qglClearColor(QColor(Qt::white));
    shaderProgram.addShaderFromSourceFile(QGLShader::Vertex, ":/vertexShader.vsh");
    shaderProgram.addShaderFromSourceFile(QGLShader::Fragment, ":/fragmentShader.fsh");
    shaderProgram.link();

    //setting the vertices
    for (int index = 0; index < nVertices; index++)
    {
        vertices << QVector3D(x[nVertexIndex], y[nVertexIndex], z[nVertexIndex])
                 << QVector3D(x[(nVertexIndex + 1)], y[(nVertexIndex + 1)], z[(nVertexIndex + 1)])
                 << QVector3D(x[(nVertexIndex + 2)], y[(nVertexIndex + 2)], z[(nVertexIndex + 2)]);
        nVertexIndex = nVertexIndex + 3;
    }
    /*************************************************/


    //setting colors
    for( int index = 0; index < nVertices; index++)
    {
        int mCount = 0;
        int xColor, yColor, zColor,sRand;
        xColor = (qrand() % 2 + 0);
        yColor = (qrand() % 2 + 0);
        zColor = (qrand() % 2 + 0);
        if ((xColor == 1) && (yColor == 1) && (zColor == 1))
        {
            sRand = (qrand() % 3 + 1);
            if ( sRand == 1)
            {
                xColor = 0;
            }
            if (sRand == 2)
            {
                yColor = 0;
            }
            if (sRand == 3)
            {
                zColor = 0;
            }
        }
        QVector<QVector3D> rColor;

        rColor << QVector3D(xColor, yColor, zColor);
        while(mCount<3)
        {
        colors << rColor;
        mCount++;
        }
    }
    /*************************************************/
}
//! [1]

void GlWidget::resizeGL(int width, int height)
{
    if (height == 0) {
        height = 1;
    }

    pMatrix.setToIdentity();
    pMatrix.perspective(60.0, (float) width / (float) height, 0.001, 1000);

    glViewport(1, 0, width, height);
}

//! [2]
void GlWidget::paintGL()
{
    //! [2]
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 mMatrix;
    QMatrix4x4 vMatrix;

    QMatrix4x4 cameraTransformation;
    cameraTransformation.rotate(alpha, 0, 1, 0);
    cameraTransformation.rotate(beta, 1, 0, 0);

    QVector3D cameraPosition = cameraTransformation * QVector3D(0, 0, distance);
    QVector3D cameraUpDirection = cameraTransformation * QVector3D(0, 1, 0);

    vMatrix.lookAt(cameraPosition, QVector3D(max_x, max_y, max_z), cameraUpDirection);

    //! [3]
    shaderProgram.bind();

    shaderProgram.setUniformValue("mvpMatrix", pMatrix * vMatrix * mMatrix);

    shaderProgram.setAttributeArray("vertex", vertices.constData());
    shaderProgram.enableAttributeArray("vertex");

    shaderProgram.setAttributeArray("color", colors.constData());
    shaderProgram.enableAttributeArray("color");

    glDrawArrays(GL_TRIANGLES, 0, vertices.size());

    shaderProgram.disableAttributeArray("vertex");

    shaderProgram.disableAttributeArray("color");

    shaderProgram.release();
}
//! [3]

void GlWidget::mousePressEvent(QMouseEvent *event)
{
    lastMousePosition = event->pos();

    event->accept();
}

void GlWidget::mouseMoveEvent(QMouseEvent *event)
{
    int deltaX = event->x() - lastMousePosition.x();
    int deltaY = event->y() - lastMousePosition.y();


    if (event->buttons() & Qt::LeftButton) {
        alpha -= deltaX;
        while (alpha < 0) {
            alpha += 360;
        }
        while (alpha >= 360) {
            alpha -= 360;
        }

        beta -= deltaY;
        if (beta < 0) {
            beta += 360;
        }
        if (beta >= 360) {
            beta -= 360;
        }

        updateGL();
    }

    lastMousePosition = event->pos();

    event->accept();
}

void GlWidget::wheelEvent(QWheelEvent *event)
{
    int delta = event->delta();

    if (event->orientation() == Qt::Vertical) {
        if (delta < 0) {
            distance *= 1.1;
        } else if (delta > 0) {
            distance *= 0.9;
        }

        updateGL();
    }

    event->accept();
}
