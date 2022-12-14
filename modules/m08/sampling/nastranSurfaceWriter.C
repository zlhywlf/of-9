/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2012-2021 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "nastranSurfaceWriter.H"
#include "polygonTriangulate.H"
#include "makeSurfaceWriterMethods.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
    makeSurfaceWriterType(nastranSurfaceWriter);
    addToRunTimeSelectionTable(surfaceWriter, nastranSurfaceWriter, wordDict);

    // create write methods
    defineSurfaceWriterWriteFields(nastranSurfaceWriter);

    template<>
    const char* NamedEnum<nastranSurfaceWriter::format, 3>::names[] =
    {
        "short",
        "long",
        "free"
    };

    const NamedEnum<nastranSurfaceWriter::format, 3>
        nastranSurfaceWriter::formatNames_;
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void Foam::nastranSurfaceWriter::formatOS(OFstream& os) const
{
    os.setf(ios_base::scientific);

    // Capitalise the E marker
    os.setf(ios_base::uppercase);

    label prec = 0;
    label offset = 7;
    switch (format_)
    {
        case (wfShort):
        case (wfFree):
        {
            prec = 8 - offset;
            break;
        }
        case (wfLong):
        {
            prec = 16 - offset;
            break;
        }
        default:
        {
        }
    }

    os.precision(prec);
}


void Foam::nastranSurfaceWriter::writeCoord
(
    const point& p,
    const label pointi,
    OFstream& os
) const
{
    // Fixed short/long formats:
    // 1 GRID
    // 2 ID   : point ID - requires starting index of 1
    // 3 CP   : co-ordinate system ID                (blank)
    // 4 X1   : point x cp-ordinate
    // 5 X2   : point x cp-ordinate
    // 6 X3   : point x cp-ordinate
    // 7 CD   : co-ordinate system for displacements (blank)
    // 8 PS   : single point constraints             (blank)
    // 9 SEID : super-element ID

    switch (format_)
    {
        case wfShort:
        {
            os.setf(ios_base::left);
            os  << setw(8) << "GRID";
            os.unsetf(ios_base::left);
            os.setf(ios_base::right);
            os  << setw(8) << pointi + 1
                << "        "
                << setw(8) << p.x()
                << setw(8) << p.y()
                << setw(8) << p.z()
                << nl;
            os.unsetf(ios_base::right);

            break;
        }
        case wfLong:
        {
            os.setf(ios_base::left);
            os  << setw(8) << "GRID*";
            os.unsetf(ios_base::left);
            os.setf(ios_base::right);
            os  << setw(16) << pointi + 1
                << "                "
                << setw(16) << p.x()
                << setw(16) << p.y()
                << nl;
            os.unsetf(ios_base::right);
            os.setf(ios_base::left);
            os  << setw(8) << "*";
            os.unsetf(ios_base::left);
            os.setf(ios_base::right);
            os  << setw(16) << p.z()
                << nl;
            os.unsetf(ios_base::right);

            break;
        }
        case wfFree:
        {
            os  << "GRID"
                << ',' << pointi + 1
                << ','
                << ',' << p.x()
                << ',' << p.y()
                << ',' << p.z()
                << nl;

            break;
        }
        default:
        {
            FatalErrorInFunction
                << "Unknown format enumeration" << abort(FatalError);
        }
    }
}

void Foam::nastranSurfaceWriter::writeFace
(
    const word& faceType,
    const labelList& facePts,
    label& nFace,
    OFstream& os
) const
{
    // Only valid surface elements are CTRIA3 and CQUAD4

    // Fixed short/long formats:
    // 1 CQUAD4
    // 2 EID  : element ID
    // 3 PID  : property element ID; default = EID   (blank)
    // 4 G1   : grid point index - requires starting index of 1
    // 5 G2   : grid point index
    // 6 G3   : grid point index
    // 7 G4   : grid point index
    // 8 onwards - not used

    // For CTRIA3 elements, cols 7 onwards are not used

    switch (format_)
    {
        case wfShort:
        {
            os.setf(ios_base::left);
            os  << setw(8) << faceType;
            os.unsetf(ios_base::left);
            os.setf(ios_base::right);
            os  << setw(8) << nFace++
                << "        ";

            forAll(facePts, i)
            {
                os  << setw(8) << facePts[i] + 1;
            }

            os  << nl;
            os.unsetf(ios_base::right);

            break;
        }
        case wfLong:
        {
            os.setf(ios_base::left);
            os  << setw(8) << word(faceType + "*");
            os.unsetf(ios_base::left);
            os.setf(ios_base::right);
            os  << setw(16) << nFace++
                << "                ";

            forAll(facePts, i)
            {
                os  << setw(16) << facePts[i] + 1;
                if (i == 1)
                {
                    os  << nl;
                    os.unsetf(ios_base::right);
                    os.setf(ios_base::left);
                    os  << setw(8) << "*";
                    os.unsetf(ios_base::left);
                    os.setf(ios_base::right);
                }
            }

            os  << nl;
            os.unsetf(ios_base::right);

            break;
        }
        case wfFree:
        {
            os  << faceType << ','
                << ++nFace << ',';

            forAll(facePts, i)
            {
                os  << ',' << facePts[i] + 1;
            }

            os  << nl;

            break;
        }
        default:
        {
            FatalErrorInFunction
                << "Unknown format enumeration" << abort(FatalError);
        }
    }

}


void Foam::nastranSurfaceWriter::writeGeometry
(
    const pointField& points,
    const faceList& faces,
    List<DynamicList<face>>& decomposedFaces,
    OFstream& os
) const
{
    // write points

    os  << "$" << nl
        << "$ Points" << nl
        << "$" << nl;

    forAll(points, pointi)
    {
        writeCoord(points[pointi], pointi, os);
    }


    // write faces

    os  << "$" << nl
        << "$ Faces" << nl
        << "$" << nl;

    label nFace = 1;

    polygonTriangulate triEngine;

    forAll(faces, facei)
    {
        const face& f = faces[facei];

        if (f.size() == 3)
        {
            writeFace("CTRIA3", faces[facei], nFace, os);
            decomposedFaces[facei].append(faces[facei]);
        }
        else if (f.size() == 4)
        {
            writeFace("CQUAD4", faces[facei], nFace, os);
            decomposedFaces[facei].append(faces[facei]);
        }
        else
        {
            // decompose poly face into tris
            triEngine.triangulate(UIndirectList<point>(points, f));
            forAll(triEngine.triPoints(), triI)
            {
                const face f(triEngine.triPoints(triI, f));
                writeFace("CTRIA3", f, nFace, os);
                decomposedFaces[facei].append(f);
            }
        }
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::nastranSurfaceWriter::nastranSurfaceWriter
(
    const IOstream::streamFormat writeFormat
)
:
    surfaceWriter(writeFormat),
    format_(wfShort),
    fieldMap_(),
    scale_(1.0)
{}


Foam::nastranSurfaceWriter::nastranSurfaceWriter(const dictionary& optDict)
:
    surfaceWriter(optDict),
    format_(wfLong),
    fieldMap_(),
    scale_(1.0)
{
    const dictionary& nastranDict(optDict.lookup("nastranOptions"));

    if (nastranDict.found("format"))
    {
        format_ = formatNames_.read(nastranDict.lookup("format"));
    }

    List<Tuple2<word, word>> fieldSet(nastranDict.lookup("fields"));

    forAll(fieldSet, i)
    {
        fieldMap_.insert(fieldSet[i].first(), fieldSet[i].second());
    }

    if (nastranDict.found("scale"))
    {
        nastranDict.lookup("scale") >> scale_;
    }
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::nastranSurfaceWriter::~nastranSurfaceWriter()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void Foam::nastranSurfaceWriter::write
(
    const fileName& outputDir,
    const fileName& surfaceName,
    const pointField& points,
    const faceList& faces
) const
{
    if (!isDir(outputDir))
    {
        mkDir(outputDir);
    }

    OFstream os(outputDir/surfaceName + ".dat");
    formatOS(os);

    if (debug)
    {
        Info<< "Writing nastran file to " << os.name() << endl;
    }

    os  << "TITLE=OpenFOAM " << surfaceName.c_str() << " mesh" << nl
        << "$" << nl
        << "BEGIN BULK" << nl;

    List<DynamicList<face>> decomposedFaces(faces.size());

    writeGeometry(points, faces, decomposedFaces, os);

    if (!isDir(outputDir))
    {
        mkDir(outputDir);
    }

    os  << "ENDDATA" << endl;
}


// ************************************************************************* //
