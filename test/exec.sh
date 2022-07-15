echo "Compilando"
g++ ./testFiles/testFiles.cpp -o ./testFiles/execTestFiles && g++ ./testResources/test.cpp -o ./testResources/execTestResources
echo "Ejecutando"
./testFiles/execTestFiles 70 && ./testResources/execTestResources 1
