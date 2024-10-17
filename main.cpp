#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <cstdlib>

using namespace std;

int main()
{
    vector<vector<int>> p;
    //Matriz de Custos de Aquisição;

    vector<vector<int>> c;
    //Matriz de Custos de Deslocação;

    int m=11;
    /*cout<<"Introduzir o nr de MP's:"<<endl;
    cin>>m;
    cout<<endl;*/

    int n=9;
    /*cout<<"Introduzir o nr de Fornecedores:"<<endl;
    cin>>n;
    cout<<endl;*/

    /*p.resize(n);
    for(int i=0; i<n; i++){
        p[i].resize(m);
    }
    c.resize(n+1);
    for(int i=0; i<=n; i++){
        c[i].resize(n+1);
    }

    cout<<"Matriz de Custos de Aquisição:\n";
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cout<<"Introduz a matriz de custos de MP"<<j+1<<" no F"<<i+1<<" (se F"<<i+1<<" nao vende MP"<<j+1<<", colocar 1000)\n";
            cin>>p[i][j];
            cout<<endl;
        }
    }

    cout<<"Matriz de Custos de Deslocacao:\n";
    for(int i=0; i<=n; i++){
        for(int j=i; j<=n; j++){
            if(j==i){
                c[i][j]=0;
            }
            else{
                cout<<"Introduza o custo de ir de "<<i<<" para "<<j<<" (se nao for possivel tal deslocacao, colocar 1000, mas pode ir-se de 0 para qualquer Fornecedor)\n";
                cin>>c[i][j];
                c[j][i]=c[i][j];
                cout<<endl;
            }
        }
    }*/

    p={{42,23,1000,14,33,1000,1000,1000,1000,1000,1000},
       {38,1000,1000,44,1000,1000,1000,29,1000,45,1000},
       {20,1000,15,1000,17,12,1000,1000,1000,24,1000},
       {1000,1000,27,1000,1000,30,34,1000,1000,21,1000},
       {29,1000,31,1000,1000,1000,1000,1000,1000,1000,35},
       {1000,28,1000,1000,1000,42,15,38,12,1000,1000},
       {1000,1000,1000,1000,36,1000,22,18,14,1000,1000},
       {1000,24,1000,32,1000,1000,1000,1000,1000,45,1000},
       {1000,1000,41,1000,26,32,1000,1000,26,1000,11}};

    c={{0,13,15,16,19,22,19,12,24,12},
       {13,0,38,1000,29,35,14,21,1000,18},
       {15,38,0,33,31,1000,20,27,35,1000},
       {16,1000,33,0,33,32,16,20,29,37},
       {19,29,31,33,0,1000,24,1000,27,29},
       {22,35,1000,32,1000,0,18,37,29,1000},
       {19,14,20,16,24,18,0,17,23,13},
       {12,21,27,20,1000,37,17,0,26,0},
       {24,1000,35,29,27,29,23,26,0,32},
       {12,18,1000,37,29,1000,13,1000,32,0}};

    cout<<"Matriz de Custos de Aquisicao:\n";
    cout<<" ";
    for(int i=0; i<m; i++){
        cout<<"  MP"<<i+1;
    }
    cout<<endl;
    for (int i = 0; i < p.size(); ++i) {
        cout<<"F"<<i+1<<" ";
        for (int j = 0; j < p[i].size(); ++j) {

            if(p[i][j]==1000){
                cout<<"--   ";

            }else{
                cout<<p[i][j]<<"   ";
            }

        }
        cout<<endl;
    }
    cout<<endl;

    cout<<"Matriz dos custos de Deslocacao: \n";
    for(int i=0; i<=n; i++){
        if(i==0){
            cout<<"   0 ";
        }
        else{
            cout<<" F"<<i;
        }
    }
    cout<<endl;

    for (int i = 0; i < c.size(); ++i){
        if(i==0){
            cout<<"0| ";
        }else
            cout<<"F"<<i<<" ";
        for (int j = 0; j < c[i].size(); ++j) {
            if(c[i][j]==1000){
                cout<<"-- ";
            }else{
                if(c[i][j]<10){
                    cout<<c[i][j]<<"  ";
                }
                else{
                    cout<<c[i][j]<<" ";
                }
            }
        }
        cout<<endl;
    }


    //FINALIZADA A PARTE DE DEFINIÇÃO DAS MATRIZES E A SUA IMPRESSÃO




    vector<int> rota;//Vetor rota
    rota.push_back(0);//começa em 0

    vector<int> aquisicao(m);//Vetor de materias primas adquiridas; tem 10 coords
    for(int i=0; i<m; i++){
        aquisicao[i]=0;      //VETOR TODO NULO; A COORD i PASSA A 1, QD A MPi FOR ADQUIRIDA
    }

    int soma=20000;//nº suf. grande
    int fornecedor=0;//1º fornecedor

    for(int i=0; i<p.size(); i++){//AQUI, VAMOS AVALIAR CADA FORNECEDOR: AQUELE QUE OFERECER UM MENOR VALOR DE DESLOCAÇÃO+MATÉRIAS PRIMAS DISPONÍVEIS (PARTINDO DE 0), SERÁ O PRIMEIRO DESTINO
        int aux=c[0][i+1];        //VAR. AUXILIAR QUE, P/ CADA FORNECEDOR, ANALISA 1º O CUSTO DE DESLOCAÇÃO A PARTIR DE 0
        for(int j=0; j<p[i].size(); j++){
            aux=aux+p[i][j];      //AQUI, A MM VAR. AUXILIAR, SOMA AO CUSTO DE DESLOCAÇÃO O CUSTO DE AQUISIÇÃO DE TODAS MATÉRIAS PRIMAS EM CADA FORNECEDOR
        }                         //NOTE-SE QUE NO CASO DE O FORNECEDOR i NÃO VENDER A MP j, O RESPETIVO CUSTO DE AQUISIÇÃO É 1000
        if(soma>aux){             //COMO OS CUSTOS DE AQUISIÇÃO E DESLOCAÇÃO SÃO ENTRE 10 E 50, SOMANDO-SE ESTES 1000 SOBE-SE NECESSARIAMENTE UMA ORDEM DE GRANDEZA, PELO QUE É POSSÍVEL TRABALHAR COM ESTE MÉTODO
            soma=aux;//AQUI, A VAR. SOMA ASSUME O VALOR MÍNIMO ENTRE TODOS OS FORNECEDORES
            fornecedor=i+1;//A VAR. FORNECEDOR DEFINE QUAL SERÁ O PRIMEIRO NODO A PASSAR DEPOIS DE 0
        }
    }

    rota.push_back(fornecedor);//FIM DA INICIAÇÃO!!!!!!!!!!!!!!!!!!!!!!!!!!!! ADICIONAMOS A ROTA O FORNECEDOR SELECIONADO

    soma=c[0][fornecedor];// DEFINE SE UMA VARIAVEL CUJO VALOR INICIAL É O CUSTO DE DESLOCACAO DA ORIGEM AO PRIMEIRO FORNECEDOR DA ROTA
    for(int i=0; i<m; i++){
        if(p[fornecedor-1][i]!=1000){
            soma=soma+p[fornecedor-1][i];//ADICIONA SE À VARIAVEL DEFINIDA ANTERIORMENTE O CUSTO DE CADA MATERIA PRIMA ADQURIDA NO PRIMEIRO FORNECEDOR DA ROTA(EXCLUINDO-SE AS MATERIAS PRIMAS NAO DISPONIVEIS)
        }
    }


    for(int i=0; i<aquisicao.size(); i++){
        if(p[fornecedor-1][i]!=1000){
            aquisicao[i]=1;//A CADA MATERIA PRIMA ADQURIDA DAMOS O VALOR DE 1 NO VETOR AQUISICAO
        }
    }

    cout<<endl<<endl<<"PASSO DE INICIACAO:\n"<<endl;

    cout<<"Nodo atual: "<<fornecedor<<endl;
    cout<<"Custo total ate agora: "<<soma<<endl;

    cout<<"Rota Atual: ";
    for(int i=0; i<rota.size(); i++){
        if(i!=rota.size()-1){
            cout<<rota[i]<<" -> ";
        }
        else{
            cout<<rota[i]<<endl<<endl;
        }
    }

    for(int i=0;i<aquisicao.size();i++){
        if(aquisicao[i]==1){
            cout<<"A MP"<<i+1<<" ja foi adquirida.\n";
        }
        else{
            cout<<"A MP"<<i+1<<" ainda nao foi adquirida.\n";
        }
    }

    cout<<endl<<endl;

    //FIM DA INICIAÇÃO!!!!!!!!!!!!!





    int somatorio=0;//DEFINE SE A VARIAVEL PARA DEFINIR QUE MATERIAS PRIMAS FALTAM ADQUIRIR
    for(int i=0; i<aquisicao.size(); i++){
        somatorio=somatorio+aquisicao[i];
    }

    int passo=0;

    while(somatorio<m){//CRITERIO DE PARAGEM --> TODAS AS MATERIAS PRIMAS SAO ADQUIRIDAS
        somatorio=0;
        passo++;//PARA DEFINIR O NUMERO DE PASSOS ITERATIVOS

        cout<<"Que materia(s) prima(s) falta(m)?:"<<endl;//INÍCIO DO PASSO ITERATIVO!!!!!!!!!!!!!!!!!!!!!!!!!!


        for(int i=0; i<aquisicao.size(); i++){
            if(aquisicao[i]==0){
                cout<<"MP: "<<i+1<<endl;
            }
        }

        cout<<endl<<"PASSO ITERATIVO "<<passo<<":\n";

        cout<<endl;

        int custos=20000;//CRIACAO DE UMA VARIAVEL COM UM VALOR SUFICIENTEMENTE GRANDE PARA DEFINIR O CUSTO DE CADA ITERACAO
        int forn=0;
        vector<int> auxilio=aquisicao;//DEFINICAO DE UM VETOR AUXILIAR COM VALOR INICIAL IGUAL AO VETOR AQUISICAO
        vector<int> auxilio2=aquisicao;//DEFINICAO DE UM SEGUNDO VETOR AUXILIAR COM VALOR INICIAL IGUAL AO VETOR AQUISICAO

        for(int i=0; i<n;i++){//TENTATIVA DE COLOCAR ISTO EM CASO GENÉRICO (PASSO ITERATIVO)
            auxilio2=auxilio;
            int aux=c[fornecedor][i+1];//DEFINIR UMA VARIAVEL AUXILIAR QUE ASSUME O VALOR INICIAL DO CUSTO DE DESLOCACAO DA ORIGEM PARA O FORNECEDOR I+1
            if(aux!=1000){//SE A DESLOCACAO FOR POSSIVEL
                for(int j=0; j<m; j++){
                    if(auxilio[j]==0){//SE A MPJ AINDA NAO TIVER SIDO ADQURIDA
                        aux=aux+p[i][j];//ADICIONAR O CUSTO DE AQUISICAO DAS MPS A VARIAVEL AUXILIAR
                        if(p[i][j]!=1000){//ADICIONAR AS MPS ADQUIRIDAS AO VETOR AUXILIO TOMANDO O VALOR 1
                            auxilio2[j]=1;
                        }
                    }
                }
                if(custos>aux){//SE O CUSTO OBTIDO FOR MENOR DO QUE O CUSTO OBTIDO ANTERIORMENTE SELECIONA SE O CUSTO MAIS BAIXO
                    custos=aux;//IGUALA SE OS CUSTOS TOTAIS A VARIAVEL AUX
                    forn=i+1;//ATUALIZA SE O FORNECEDOR
                    aquisicao=auxilio2;//ATUALIZAR O VETOR AQUISICAO
                }
            }
        };

        rota.push_back(forn);//ADICIONAR O FORNECEDOR A ROTA

        soma=soma+c[fornecedor][forn];//ATUALIZAR O CUSTO TOTAL ADICIONANDO A DESLOCACAO DO FORNECEDOR PREVIAMENTE ESCOLHIDO PARA O O FORNECEDOR ESCOLHIDO AGORA
        for(int i=0; i<m; i++){
            if(auxilio[i]==0 and aquisicao[i]==1){//ATUALIZAR O CUSTO TOTAL COM A AQUISICAO DAS MATERIAS PRIMAS AINDA EM FALTA, DISPONIVEIS NO FORNECEDOR ESCOLHIDO AGORA
                if(p[forn-1][i]!=1000){
                    soma=soma+p[forn-1][i];
                    auxilio[i]=1;
                }
            }
        }

        fornecedor=forn;//ATUALIZAR O FORNECEDOR

        cout<<"Nodo atual: "<<fornecedor<<endl;
        cout<<"Custo total ate agora: "<<soma<<endl;
        cout<<"Rota Atual: ";
        for(int i=0; i<rota.size(); i++){
            if(i!=rota.size()-1){
                cout<<rota[i]<<" -> ";
            }
            else{
                cout<<rota[i]<<endl<<endl;
            }
        }

        for(int i=0;i<aquisicao.size();i++){
            if(aquisicao[i]==1){
                cout<<"A MP"<<i+1<<" ja foi adquirida.\n";
            }
            else{
                cout<<"A MP"<<i+1<<" ainda nao foi adquirida.\n";
            }
        }
        cout<<endl<<endl;

        for(int i=0; i<aquisicao.size(); i++){//ATUALIZAR O VALOR DA VARIAVEL SOMATORIO COM AS MPS ADQUIRIDAS TOMANDO O VALOR 1
            somatorio=somatorio+aquisicao[i];
        }
    }

    cout<<endl<<endl<<"Todas as MP's ja foram adquiridas  <=> STOP!"<<endl<<"Vamos regressar para 0.\n";
    rota.push_back(0);//ADICIONAR A ORIGEM A ROTA
    soma=soma+c[fornecedor][0];//ADICIONAR AO CUSTO TOTAL A DESLOCACAO DO ULTIMO FORNECEDOR A ORIGEM
    cout<<"Nodo atual: "<<0<<".\n"<<"Custo Total: "<<soma<<".\n";
    cout<<"Rota final: ";
    for(int i=0; i<rota.size(); i++){
        if(i!=rota.size()-1){
            cout<<rota[i]<<" -> ";
        }
        else{
            cout<<rota[i]<<endl<<endl;
        }
    }

    cout<<endl;


    cout<<"Vamos analisar a seguinte vizinhanca da solucao inicial:\n";
    cout<<"QUAIS AS SOlUCOES ADMISSIVEIS, TROCANDO CADA NODO DA SOLUCAO INICIAL POR UM NODO QUE NAO ESTEJA A SER EXPLORADO?\n";
    cout<<endl<<endl;

    vector<int> explorado(n);  //ANALISAR QUE NODOS JA FORAM ANALISADOS E QUAIS NAO FORAM - VETOR BINARIO

    for(int i=0;i<n;i++){
        explorado[i]=0;
        for(int j=0; j<rota.size(); j++){
            if(rota[j]==i+1){
                explorado[i]=1;  //1 SE JA EXPLORADO; 2 SE NAO
            }
        }
    }

    for(int i=0; i<n; i++){
        if(explorado[i]==1){
            cout<<"O nodo "<<i+1<<" esta a ser explorado;\n";
        }
        else{
            cout<<"O nodo "<<i+1<<" nao esta a ser explorado;\n";
        }
    }


    //O OBJETIVO AGORA E CRIAR CICLOS QUE FACAM O SEGUINTE:
    //EM 1º LUGAR, VAMOS ANALISAR O 1º NODO DA SOL. INICIAL; VAMOS ANALISAR O QUE ACONTECE SE TROCARMOS ESTE NODO POR CADA UM DOS NODOS QUE ESTÃO FORA DA SOL. INICIAL
    //VAMOS FAZER ISTO PARA CADA UM DOS NODOS
    //POSTERIORMENTE, TEMOS DE CONSEGUIR AVALIAR SE AS SOLUCOES GERADAS SAO ADMISSIVEIS OU NAO
    //FINALMENTE, TEMOS DE LISTAR AS ADMISSIVEIS
    //POSTERIORMENTE, QUEREMOS SABER SE HÁ ÓTIMOS LOCAIS; NO CASO DE HAVER (I.E. UMA SOL. DA VIZINHANÇA C/ CUSTO +BAIXO QUE O DA SOL. INICIAL)
    //NO CASO DE HAVER, TEMOS DE FAZER UM PROGRAMA QUE ANALISE A VIZINHANÇA GERADA POR ESTA SOLUCAO, E DEMONSTRAR QUE E OTIMA

    // Criacao da vizinhanca da solucao inicial
    cout <<endl<<endl<< "Criando a vizinhanca da solucao inicial:" << endl<<endl;


    vector<vector<int>> vizinhanca={rota}; //CRIAR MATRIZ VIZINHANÇA, COM A 1ª LINHA IGUAL À SOLUÇÃO INICIAL
    vector<int> custos_totais={soma}; //CRIAR VETOR DE CUSTOS, A ROTA i NA MATRIZ DA VIZINHANCA TEM O CUSTO i NO VETOR DE CUSTOS

    for (int i = 1; i < rota.size() - 1; i++) {
        int no_excluido = rota[i];  //VAMOS EXCLUIR UM NODO DA ROTA INICIAL E ITERAR SOBRE ELE; VAMOS SUBSTITUÍ-LO POR CADA UM DOS NODOS INEXPLORADOS
        int nodo_anterior=rota[i-1]; //NODO ANTERIOR AO EXCLUÍDO
        int nodo_seguinte=rota[i+1]; // SEGUINTE AO EXCLUÍDO

        for (int j = 0; j < n; j++) {
            int custoVIR=c[j+1][nodo_anterior]; //ANALISAR O CUSTO DE DESLOCAÇÃO DO NODO QUE FOI INSERIDO EM SUBSTITUIÇÃO
            int custoIR=c[j+1][nodo_seguinte]; //TANTO DO NODO ANTERIOR COMO PARA O SEGUINTE NA ROTA
            if (explorado[j] == 0 && j + 1 != no_excluido && custoVIR!=1000 && custoIR!=1000) { //GARANTIR QUE SO ANALISAMOS A TROCA COM NODOS DIFERENTES DO EXCLUIDO, INEXPLORADOS E QUE PODEM ENTRAR NA ROTA NAQUELAS POSICOES
                vector<int> nova_rota=rota;
                nova_rota[i]=j+1;
                int custo_nova_rota=0;

                // Verificar se a nova rota e admissivel
                vector<int> mp_adquiridas(m, 0);
                bool admissivel = true;

                for (int k = 1; k < nova_rota.size()-1; k++) {
                    int fornecedor_atual = nova_rota[k];
                    int fornecedor_anterior = nova_rota[k-1];
                    custo_nova_rota=custo_nova_rota+c[fornecedor_anterior][fornecedor_atual];  //RECOLHER O CUSTO DE CADA ROTA NOVA

                    for (int l = 0; l < m; l++) {
                        if (p[fornecedor_atual-1][l] != 1000 && mp_adquiridas[l]==0) {
                            mp_adquiridas[l] = 1;  //ACUMULAR QUE MATERIAS PRIMAS JA FORAM ADQUIRIDAS
                            custo_nova_rota=custo_nova_rota+p[fornecedor_atual-1][l];
                        }
                    }

                    if(k==nova_rota.size()-2){
                        custo_nova_rota=custo_nova_rota+c[fornecedor_atual][0];//CUSTO DE REGRESSO
                    }

                }

                for (int k = 0; k < m; k++) {
                    if (mp_adquiridas[k] == 0) {
                        admissivel = false;  //CONDICAO DE ADMISSIBILIDADE
                        break;
                    }
                }

                if (admissivel) {
                    vizinhanca.push_back(nova_rota);  //SE ADMISSIVEL, ADICIONAR A ROTA A MATRIZ DA VIZINHANCA
                    custos_totais.push_back(custo_nova_rota);  //E ADICIONAR O CUSTO AO VETOR DE CUSTOS
                }
            }
        }
    }

    // Exibir soluções admissíveis na vizinhança
    cout << "Solucoes admissiveis na vizinhanca:\n" << endl;
    for (int i = 0; i < vizinhanca.size(); i++) {
        if(i==0){
            cout<<"Solucao "<<i<<" (ROTA INICIAL):";
            for (int j = 0; j < vizinhanca[i].size(); j++) {
                if(j!=vizinhanca[i].size()-1){
                    cout<<vizinhanca[i][j]<<" -> ";
                }
                else{
                    cout<<vizinhanca[i][j]<<endl;;
                }
            }
            cout<<"Custo associado: "<<custos_totais[i]<<endl;;
        }
        else{
            cout << "Solucao " << i << ": ";
            for (int j = 0; j < vizinhanca[i].size(); j++) {
                if(j!=vizinhanca[i].size()-1){
                    cout<<vizinhanca[i][j]<<" -> ";
                }
                else{
                    cout<<vizinhanca[i][j]<<endl;
                }
            }
            cout<<"Custo associado: "<<custos_totais[i]<<endl;
        }
        cout<<endl;
    }

    int minimo=20000;

    for(int i=0; i<custos_totais.size(); i++){
        if(minimo>custos_totais[i]){
            minimo=custos_totais[i];  //ANALISAR QUE ROTA TEM O CUSTO MAIS BAIXO DA VIZINHANCA (OTIMO LOCAL)
        }
    }

    cout<<endl<<"O otimo local da vizinhanca encontrada corresponde ao custo total: "<<minimo<<"\n";
    cout<<"Este valor corresponde a seguinte rota:\n";

    for(int i=0; i<vizinhanca.size();i++){
        if(custos_totais[i]==minimo){   //EM CASO DE EMPATE, É ARBITRÁRIO
            for(int j=0;j<vizinhanca[i].size();j++){
                if(j!=vizinhanca[i+1].size()-1){
                    cout<<vizinhanca[i][j]<<" -> ";
                }
                else{
                    cout<<vizinhanca[i][j];
                }
            }
            cout<<endl;
            break;
        }
    }

    int soma2=soma;
    vector<int> rota_atual;

    if(minimo==soma){
        cout<<endl<<endl<<"O otimo local corresponde a solucao inicial determinada.\n"<<endl;
    }
    else{
        while(minimo<soma2){ //CRIACAO DE CICLO (SEMELHANTE AO DESENVOVIDO PARA A VIZINHANÇA INICIAL) QUE PESQUISE, PELO MESMO MÉTODO, AS ROTAS ADMISSÍVEIS DA VIZINHANÇA DE CADA ÓTIMO LOCAL, ATÉ QUE SE CHEGUE A UM ÓTIMO LOCAL FINAL (ÓTIMO DA VIZINHANÇA GERADA POR SI)
            cout<<endl<<endl<<"O otimo local corresponde a uma solucao admissivel, que se encontra na vizinhanca da solucao determinada."<<endl<<"Assim, vamos identificar se este corresponde ao otimo da vizinhanca que e gerada da mesma forma sobre esta solucao.\n";
            soma2=minimo;
            for(int i=0; i<vizinhanca[i].size(); i++){
                if(custos_totais[i]==minimo){
                    rota_atual=vizinhanca[i];
                    break;
                }
            }

            vector<int> explorado2(n);

            for(int i=0;i<n;i++){
                explorado2[i]=0;
                for(int j=0; j<rota_atual.size(); j++){
                    if(rota_atual[j]==i+1){
                        explorado2[i]=1;
                    }
                }
            }

            vector<vector<int>> vizinhanca2={rota_atual};
            vector<int> custos_totais2={minimo};

            for (int i = 1; i < rota_atual.size() - 1; i++) {
                int no_excluido = rota_atual[i];
                int nodo_anterior=rota_atual[i-1];
                int nodo_seguinte=rota_atual[i+1];

                for (int j = 0; j < n; j++) {
                    int custoVIR=c[j+1][nodo_anterior];
                    int custoIR=c[j+1][nodo_seguinte];
                    if (explorado2[j] == 0 && j + 1 != no_excluido && custoVIR!=1000 && custoIR!=1000) {
                        vector<int> nova_rota=rota_atual;
                        nova_rota[i]=j+1;
                        int custo_nova_rota=0;

                        // Verificar se a nova rota e admissivel
                        vector<int> mp_adquiridas(m, 0);
                        bool admissivel = true;

                        for (int k = 1; k < nova_rota.size()-1; k++) {
                            int fornecedor_atual = nova_rota[k];
                            int fornecedor_anterior = nova_rota[k-1];
                            custo_nova_rota=custo_nova_rota+c[fornecedor_anterior][fornecedor_atual];

                            for (int l = 0; l < m; l++) {
                                if (p[fornecedor_atual-1][l] != 1000 && mp_adquiridas[l]==0) {
                                    mp_adquiridas[l] = 1;
                                    custo_nova_rota=custo_nova_rota+p[fornecedor_atual-1][l];
                                }
                            }

                            if(k==nova_rota.size()-2){
                                custo_nova_rota=custo_nova_rota+c[fornecedor_atual][0];
                            }

                        }

                        for (int k = 0; k < m; k++) {
                            if (mp_adquiridas[k] == 0) {
                                admissivel = false;
                                break;
                            }
                        }

                        if (admissivel) {
                            vizinhanca2.push_back(nova_rota);
                            custos_totais2.push_back(custo_nova_rota);
                        }
                    }
                }
            }
            // Exibir soluções admissíveis na vizinhança
            cout << "Solucoes admissiveis na vizinhanca:\n" << endl;
            for (int i = 0; i < vizinhanca2.size(); i++) {
                if(i==0){
                    cout<<"Solucao "<<i<<" (ROTA DE PARTIDA):";
                    for (int j = 0; j < vizinhanca2[i].size(); j++) {
                        if(j!=vizinhanca2[i].size()-1){
                            cout<<vizinhanca2[i][j]<<" -> ";
                        }
                        else{
                            cout<<vizinhanca2[i][j]<<endl;;
                        }
                    }
                    cout<<"Custo associado: "<<custos_totais2[i]<<endl;;
                }
                else{
                    cout << "Solucao " << i << ": ";
                    for (int j = 0; j < vizinhanca2[i].size(); j++) {
                        if(j!=vizinhanca2[i].size()-1){
                            cout<<vizinhanca2[i][j]<<" -> ";
                        }
                        else{
                            cout<<vizinhanca2[i][j]<<endl;
                        }
                    }
                    cout<<"Custo associado: "<<custos_totais2[i]<<endl;
                }
                cout<<endl;
            }
            for(int i=0; i<custos_totais2.size(); i++){
                if(minimo>custos_totais2[i]){
                    minimo=custos_totais2[i];
                }
            }
        }
    }

    cout<<endl<<endl;

    cout<<"O otimo local final corresponde a rota: \n";

    for(int i=0; i<rota_atual.size(); i++){
        if(i!=rota_atual.size()-1){
            cout<<rota_atual[i]<<" -> ";
        }
        else{
            cout<<rota_atual[i]<<endl;
        }
    }
    cout<<"Com o custo associado: "<<minimo<<endl<<endl;










    //METAHEURISTICA

    cout<<endl<<endl<<"Vamos agora aplicar uma metaheuristica que crie uma perturbacao na solucao que consideramos como melhor, de forma a escapar ao otimo local."<<endl<<"Para tal, vamos retirar a rota determinada o primeiro e o segundo nodo, distribuindo-os aleatoriamente pela rota.\n"<<endl;
    cout<<"No caso de encontrarmos uma solucao perturbada admissivel, vamos realizar busca local sobre ela.  No caso de, na sua vizinhanca (gerada do mesmo modo), encontrarmos um otimo local que seja melhor que a solucao determinada, esta sera a rota a perturbar na iteracao seguinte.\n"<<endl<<endl<<endl;

    srand(3);

    int nr_iteracoes=1;

    vector<vector<int>> iteracoes={rota_atual};

    int posicaoAleatoria1;
    int posicaoAleatoria2;

    vector<int> rotaPerturbada(rota_atual.size(),0);

    vector<int> fornecedoresConstantes;

    bool diferente;
    int contador;
    bool admiss=true;

    vector<int> nodosDiferentes;
    vector<int> materiasPrimas(m,0);
    vector<int> MPs(m,0);

    int custoAtual=0;

    while (nr_iteracoes<6){

        posicaoAleatoria1 = rand() % (rota_atual.size() - 2) + 1;  //ESCOLHA DE 2 POSICOES ALEATÓRIAS
        posicaoAleatoria2 = rand() % (rota_atual.size() - 2) + 1;

        while(posicaoAleatoria1==posicaoAleatoria2){
            posicaoAleatoria2 = rand() % (rota_atual.size() - 2) + 1;
        }

        if (rota_atual.size() <= 3) {
            cout<<"Nao e possivel remover cidades se houver menos de 3 cidades na rota que esta a ser analisada.\n";
            break;
        }

        rotaPerturbada.resize(rota_atual.size());

        for(int i=0; i<rotaPerturbada.size(); i++){
            rotaPerturbada[i]=0;
        }

        rotaPerturbada[posicaoAleatoria1] = rota_atual[1];

        rotaPerturbada[posicaoAleatoria2] = rota_atual[2];

        fornecedoresConstantes={};

        for(int i=0; i<rota_atual.size(); i++){
            if(i!=1 and i!=2){
                fornecedoresConstantes.push_back(rota_atual[i]);
            }
        }

        contador=1;

        for(int i=1; i<rota_atual.size()-1; i++){
            if(i!=posicaoAleatoria1 and i!=posicaoAleatoria2){
                rotaPerturbada[i]=fornecedoresConstantes[contador];
                contador++;
            }
        }//ROTA PERTURBADA DEFINIDA

        nodosDiferentes.resize(rotaPerturbada.size());

        iteracoes.push_back(rotaPerturbada);

        admiss=true;

        for(int i=1; i<rotaPerturbada.size(); i++){
            if(i!=rotaPerturbada.size()-1){
                int nodoAgora=rotaPerturbada[i];
                int proximoNodo=rotaPerturbada[i+1];
                if(c[nodoAgora][proximoNodo]==1000){
                    admiss=false;
                    break;
                }
            }
        }

        for(int i=0; i<m; i++){
            MPs[i]=0;
        }

        if(admiss==true){  //AVALIAR A ADMISSIBILIDADE DAS ROTAS PERTURBADAS
            for(int i=1; i<rotaPerturbada.size()-1; i++){
                int nodoAgora=rotaPerturbada[i];
                for(int j=0; j<m; j++){
                    if(p[nodoAgora-1][j]!=1000){
                        materiasPrimas[j]=1;
                    }
                }
            }

            for(int i=0; i<m; i++){
                if(materiasPrimas[i]==0){
                    admiss=false;
                }
            }
        }

        if(admiss==true){
            cout<<"A rota perturbada "<<nr_iteracoes<<" e admissivel e corresponde a rota: \n";
            for(int i=0; i<rotaPerturbada.size(); i++){
                if(i!=rotaPerturbada.size()-1){
                    cout<<rotaPerturbada[i]<<" -> ";
                }
                else{
                    cout<<rotaPerturbada[i]<<endl;
                }
            }

            custoAtual=0;

            for(int i=0;i<rotaPerturbada.size()-1; i++){
                int nodo1=rotaPerturbada[i];
                int nodo2=rotaPerturbada[i+1];
                custoAtual=custoAtual+c[nodo1][nodo2];
            }

            for(int i=1;i<rotaPerturbada.size()-1; i++){
                int nodoA=rotaPerturbada[i];
                for(int j=0; j<m; j++){
                    if(p[nodoA-1][j]!=1000 and MPs[j]==0){
                        custoAtual=custoAtual+p[nodoA-1][j];
                        MPs[j]=1;
                    }
                }
            }

            cout<<"Com o custo associado: "<<custoAtual<<endl<<endl;

            //AQUI, ANALISAMOS A VIZINHANCA DA SOLUCAO PERTURBADA, A VER SE NELA ENCONTRAMOS UMA SOLUCAO ADMISSIVEL PARA A QUAL O CUSTO TOTAL SEJA INFERIOR AO CUSTO QUE TINHAMOS ANTERIRORMENTE



            cout <<endl<<endl<< "Criando a vizinhanca da solucao perturbada:" << endl<<endl;

            vector<int> explorado3(n);

            for(int i=0;i<n;i++){
                explorado3[i]=0;
                for(int j=0; j<rotaPerturbada.size(); j++){
                    if(rotaPerturbada[j]==i+1){
                        explorado3[i]=1;
                    }
                }
            }
            vector<vector<int>> vizinhanca3={rotaPerturbada}; //CRIAR MATRIZ VIZINHANÇA, COM A 1ª LINHA IGUAL À SOLUÇÃO PERTURBADA
            vector<int> custos_totais3={custoAtual}; //CRIAR VETOR DE CUSTOS, A ROTA i NA MATRIZ DA VIZINHANCA TEM O CUSTO i NO VETOR DE CUSTOS

            for (int i = 1; i < rotaPerturbada.size() - 1; i++) {
                int no_excluido = rotaPerturbada[i];  //VAMOS EXCLUIR UM NODO DA ROTA PERTURBADA E ITERAR SOBRE ELE; VAMOS SUBSTITUÍ-LO POR CADA UM DOS NODOS INEXPLORADOS
                int nodo_anterior=rotaPerturbada[i-1]; //NODO ANTERIOR AO EXCLUÍDO
                int nodo_seguinte=rotaPerturbada[i+1]; // SEGUINTE AO EXCLUÍDO

                for (int j = 0; j < n; j++) {
                    int custoVIR=c[j+1][nodo_anterior]; //ANALISAR O CUSTO DE DESLOCAÇÃO DO NODO QUE FOI INSERIDO EM SUBSTITUIÇÃO
                    int custoIR=c[j+1][nodo_seguinte]; //TANTO DO NODO ANTERIOR COMO PARA O SEGUINTE NA ROTA
                    if (explorado3[j] == 0 && j + 1 != no_excluido && custoVIR!=1000 && custoIR!=1000) { //GARANTIR QUE SO ANALISAMOS A TROCA COM NODOS DIFERENTES DO EXCLUIDO, INEXPLORADOS E QUE PODEM ENTRAR NA ROTA NAQUELAS POSICOES
                        vector<int> nova_rota=rotaPerturbada;
                        nova_rota[i]=j+1;
                        int custo_nova_rota=0;

                        // Verificar se a nova rota e admissivel
                        vector<int> mp_adquiridas(m, 0);
                        bool admissivel = true;

                        for (int k = 1; k < nova_rota.size()-1; k++) {
                            int fornecedor_atual = nova_rota[k];
                            int fornecedor_anterior = nova_rota[k-1];
                            custo_nova_rota=custo_nova_rota+c[fornecedor_anterior][fornecedor_atual];  //RECOLHER O CUSTO DE CADA ROTA NOVA

                            for (int l = 0; l < m; l++) {
                                if (p[fornecedor_atual-1][l] != 1000 && mp_adquiridas[l]==0) {
                                    mp_adquiridas[l] = 1;  //ACUMULAR QUE MATERIAS PRIMAS JA FORAM ADQUIRIDAS
                                    custo_nova_rota=custo_nova_rota+p[fornecedor_atual-1][l];
                                }
                            }

                            if(k==nova_rota.size()-2){
                                custo_nova_rota=custo_nova_rota+c[fornecedor_atual][0];//CUSTO DE REGRESSO
                            }

                        }

                        for (int k = 0; k < m; k++) {
                            if (mp_adquiridas[k] == 0) {
                                admissivel = false;  //CONDICAO DE ADMISSIBILIDADE
                                break;
                            }
                        }

                        if (admissivel) {
                            vizinhanca3.push_back(nova_rota);  //SE ADMISSIVEL, ADICIONAR A ROTA A MATRIZ DA VIZINHANCA
                            custos_totais3.push_back(custo_nova_rota);  //E ADICIONAR O CUSTO AO VETOR DE CUSTOS
                        }
                    }
                }
            }

            // Exibir soluções admissíveis na vizinhança
            cout << "Solucoes admissiveis na vizinhanca:\n" << endl;
            for (int i = 0; i < vizinhanca3.size(); i++) {
                if(i==0){
                    cout<<"Solucao "<<i<<" (ROTA PERTURBADA):";
                    for (int j = 0; j < vizinhanca3[i].size(); j++) {
                        if(j!=vizinhanca3[i].size()-1){
                            cout<<vizinhanca3[i][j]<<" -> ";
                        }
                        else{
                            cout<<vizinhanca3[i][j]<<endl;;
                        }
                    }
                    cout<<"Custo associado: "<<custos_totais3[i]<<endl;;
                }
                else{
                    cout << "Solucao " << i << ": ";
                    for (int j = 0; j < vizinhanca3[i].size(); j++) {
                        if(j!=vizinhanca3[i].size()-1){
                            cout<<vizinhanca3[i][j]<<" -> ";
                        }
                        else{
                            cout<<vizinhanca3[i][j]<<endl;
                        }
                    }
                    cout<<"Custo associado: "<<custos_totais3[i]<<endl;
                }
                cout<<endl;
            }

            int valor=20000;

            for(int i=0; i<custos_totais3.size(); i++){
                if(valor>custos_totais3[i]){
                    valor=custos_totais3[i];  //ANALISAR QUE ROTA TEM O CUSTO MAIS BAIXO DA VIZINHANCA (OTIMO LOCAL)
                }
            }

            cout<<endl<<"O otimo local da vizinhanca encontrada corresponde ao custo total: "<<valor<<"\n";
            cout<<"Este valor corresponde a seguinte rota:\n";

            for(int i=0; i<vizinhanca3.size();i++){
                if(custos_totais3[i]==valor){   //EM CASO DE EMPATE, É ARBITRÁRIO
                    for(int j=0;j<vizinhanca3[i].size();j++){
                        if(j!=vizinhanca3[i+1].size()-1){
                            cout<<vizinhanca3[i][j]<<" -> ";
                        }
                        else{
                            cout<<vizinhanca3[i][j];
                        }
                    }
                    cout<<endl;
                    break;
                }
            }

            if(valor<minimo){
                cout<<endl<<endl<<"O otimo local sera a proxima solucao a perturbar.\n"<<endl;
                for(int i=0; i<vizinhanca3.size(); i++){
                    if(valor==custos_totais3[i]){
                        rota_atual=vizinhanca3[i];
                    }
                }
                minimo=valor;
            }
            else{
                cout<<endl<<endl<<"A rota antes de perturbacoes continua a ser melhor que qualquer uma das que se encontram na vizinhanca da rota perturbada. Vamos perturbar de novo:\n"<<endl;
            }


            //ATÉ AQUI FOI COPIAR E ALTERAR O NOSSO ALGORITMO DE BUSCA DE VIZINHANCA; ESTÁ CORRETO; JÁ O CONFIRMÁMOS, NÃO TEMOS PROBLEMAS NISSO



        }
        else{
            cout<<"A rota perturbada "<<nr_iteracoes<<" nao e admissivel:\n";
            for(int i=0; i<rotaPerturbada.size(); i++){
                if(i!=rotaPerturbada.size()-1){
                    cout<<rotaPerturbada[i]<<" -> ";
                }
                else{
                    cout<<rotaPerturbada[i]<<endl<<endl;
                }
            }
        }

        nr_iteracoes++;

    }

    cout<<endl<<endl<<"Apos a execucao da metaheuristica, conclui-se que a melhor solucao e:\n";
    for(int i=0; i<rota_atual.size(); i++){
        if(i!=rota_atual.size()-1){
            cout<<rota_atual[i]<<" -> ";
        }
        else{
            cout<<rota_atual[i];
        }
    }

    cout<<endl<<"Com o custo associado: "<<minimo<<endl<<endl;

    return 0;

}
