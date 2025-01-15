%% About definematrixOperations.m
% This file defines the MATLAB interface to the library |matrixOperations|.
%
% Commented sections represent C++ functionality that MATLAB cannot automatically define. To include
% functionality, uncomment a section and provide values for <SHAPE>, <DIRECTION>, etc. For more
% information, see helpview(fullfile(docroot,'matlab','helptargets.map'),'cpp_define_interface') to "Define MATLAB Interface for C++ Library".



%% Setup
% Do not edit this setup section.
function libDef = definematrixOperations()
libDef = clibgen.LibraryDefinition("matrixOperationsData.xml");

%% OutputFolder and Libraries 
libDef.OutputFolder = "D:\PROJECT\전기차\EVSE100A\FT2232_API\LibMPSSE_1.0.5\LibMPSSE_1.0.5\Windows\libmpsse-windows-1.0.5\release\matlabDLL";
libDef.Libraries = "C:\Program Files\MATLAB\R2024a\extern\examples\cpp_interface\win64\mingw64\matrixOperations.lib";

%% C++ class |Mat| with MATLAB name |clib.matrixOperations.Mat| 
MatDefinition = addClass(libDef, "Mat", "MATLABName", "clib.matrixOperations.Mat", ...
    "Description", "clib.matrixOperations.Mat    Representation of C++ class Mat."); % Modify help description values as needed.

%% C++ class constructor for C++ class |Mat| 
% C++ Signature: Mat::Mat(Mat const & input1)

MatConstructor1Definition = addConstructor(MatDefinition, ...
    "Mat::Mat(Mat const & input1)", ...
    "Description", "clib.matrixOperations.Mat Constructor of C++ class Mat."); % Modify help description values as needed.
defineArgument(MatConstructor1Definition, "input1", "clib.matrixOperations.Mat", "input");
validate(MatConstructor1Definition);

%% C++ class constructor for C++ class |Mat| 
% C++ Signature: Mat::Mat()

MatConstructor2Definition = addConstructor(MatDefinition, ...
    "Mat::Mat()", ...
    "Description", "clib.matrixOperations.Mat Constructor of C++ class Mat."); % Modify help description values as needed.
validate(MatConstructor2Definition);

%% C++ class method |setMat| for C++ class |Mat| 
% C++ Signature: void Mat::setMat(int [] src,size_t len)

%setMatDefinition = addMethod(MatDefinition, ...
%    "void Mat::setMat(int [] src,size_t len)", ...
%    "MATLABName", "setMat", ...
%    "Description", "setMat Method of C++ class Mat."); % Modify help description values as needed.
%defineArgument(setMatDefinition, "src", "clib.array.matrixOperations.Int", "input", <SHAPE>); % <MLTYPE> can be "clib.array.matrixOperations.Int", or "int32"
%defineArgument(setMatDefinition, "len", "uint64");
%validate(setMatDefinition);

%% C++ class method |getMat| for C++ class |Mat| 
% C++ Signature: int const * const Mat::getMat(size_t len) const

%getMatDefinition = addMethod(MatDefinition, ...
%    "int const * const Mat::getMat(size_t len) const", ...
%    "MATLABName", "getMat", ...
%    "Description", "getMat Method of C++ class Mat."); % Modify help description values as needed.
%defineArgument(getMatDefinition, "len", "uint64");
%defineOutput(getMatDefinition, "RetVal", "clib.array.matrixOperations.Int", <SHAPE>); % <MLTYPE> can be "clib.array.matrixOperations.Int", or "int32"
%validate(getMatDefinition);

%% C++ class method |getLength| for C++ class |Mat| 
% C++ Signature: size_t Mat::getLength() const

getLengthDefinition = addMethod(MatDefinition, ...
    "size_t Mat::getLength() const", ...
    "MATLABName", "getLength", ...
    "Description", "getLength Method of C++ class Mat."); % Modify help description values as needed.
defineOutput(getLengthDefinition, "RetVal", "uint64");
validate(getLengthDefinition);

%% C++ class method |copyMat| for C++ class |Mat| 
% C++ Signature: void Mat::copyMat(int * dest,size_t len)

%copyMatDefinition = addMethod(MatDefinition, ...
%    "void Mat::copyMat(int * dest,size_t len)", ...
%    "MATLABName", "copyMat", ...
%    "Description", "copyMat Method of C++ class Mat."); % Modify help description values as needed.
%defineArgument(copyMatDefinition, "dest", "clib.array.matrixOperations.Int", "input", <SHAPE>); % <MLTYPE> can be "clib.array.matrixOperations.Int", or "int32"
%defineArgument(copyMatDefinition, "len", "uint64");
%validate(copyMatDefinition);

%% C++ function |addMat| with MATLAB name |clib.matrixOperations.addMat|
% C++ Signature: int addMat(Mat const * mat)

%addMatDefinition = addFunction(libDef, ...
%    "int addMat(Mat const * mat)", ...
%    "MATLABName", "clib.matrixOperations.addMat", ...
%    "Description", "clib.matrixOperations.addMat Representation of C++ function addMat."); % Modify help description values as needed.
%defineArgument(addMatDefinition, "mat", "clib.matrixOperations.Mat", "input", <SHAPE>); % <MLTYPE> can be "clib.matrixOperations.Mat", or "clib.array.matrixOperations.Mat"
%defineOutput(addMatDefinition, "RetVal", "int32");
%validate(addMatDefinition);

%% C++ function |updateMatByX| with MATLAB name |clib.matrixOperations.updateMatByX|
% C++ Signature: void updateMatByX(Mat & mat,int X)

updateMatByXDefinition = addFunction(libDef, ...
    "void updateMatByX(Mat & mat,int X)", ...
    "MATLABName", "clib.matrixOperations.updateMatByX", ...
    "Description", "clib.matrixOperations.updateMatByX Representation of C++ function updateMatByX."); % Modify help description values as needed.
defineArgument(updateMatByXDefinition, "mat", "clib.matrixOperations.Mat", "input");
defineArgument(updateMatByXDefinition, "X", "int32");
validate(updateMatByXDefinition);

%% C++ function |updateMatBySize| with MATLAB name |clib.matrixOperations.updateMatBySize|
% C++ Signature: void updateMatBySize(Mat & mat,int * arr,size_t len)

%updateMatBySizeDefinition = addFunction(libDef, ...
%    "void updateMatBySize(Mat & mat,int * arr,size_t len)", ...
%    "MATLABName", "clib.matrixOperations.updateMatBySize", ...
%    "Description", "clib.matrixOperations.updateMatBySize Representation of C++ function updateMatBySize."); % Modify help description values as needed.
%defineArgument(updateMatBySizeDefinition, "mat", "clib.matrixOperations.Mat", "input");
%defineArgument(updateMatBySizeDefinition, "arr", "clib.array.matrixOperations.Int", "input", <SHAPE>); % <MLTYPE> can be "clib.array.matrixOperations.Int", or "int32"
%defineArgument(updateMatBySizeDefinition, "len", "uint64");
%validate(updateMatBySizeDefinition);

%% Validate the library definition
validate(libDef);

end
