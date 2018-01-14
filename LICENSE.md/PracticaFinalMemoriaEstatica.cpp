/***************************************************************************************/
/* 									PRÀCTICA FINAL                                     */
/* 						Gonzalo Murillo Tello | 1 Física         				       */
/***************************************************************************************/
#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;
//Definició de constants
#define TAM 1000 // Màxim de fitxes
# define INF 99999 // Variable para inicializar la estructura que guarda los cálculos de distancia (compatibilidad)
# define PUNTPEROPERACIO 10000000
# define PUNTPEROPERACIODISTANCIA 1000
//Estructura

// Una estructura para guardar la compatibilidad entre personas. Para ello se utilizara un vector de este tipo de estructuras.
struct compatibilidad
{
	// Contendra datos de la relacion entre 1 y 2
	int i; // posicion de la persona origen en el vector de personas
	int j; // posicion de la persona destino en el vector de personas
	float DistanciaManhattan; 
	int AfinidadHobbies;
	int diferenciaEdad;
    int diferenciaSexe;
	double pt;

// Inicializacio per defecte
compatibilidad(): i(-1),j(-1), DistanciaManhattan(INF), AfinidadHobbies(INF), diferenciaEdad(INF),diferenciaSexe(INF),pt(0) { }   
 
};

// Una estructura para guardar los datos de las personas
struct persona
{
	string nom, correu;
	float latitud, longitud;
	int musica, cine, any;
	char sexe;
};

// Calcula la distancia de Manhattan entre dos personas (pasadas como struct del tipo persona)

float CalculaManhattan(persona o, persona d)
{
	// Siendo	M=(x0;y0) N=(x1;y1), entonces DM(M:N)=|x1-x0|+|y1-y0|

	float DM=0;
	DM=abs(d.latitud-o.latitud)+abs(d.longitud-o.longitud);

	return DM;
}


// Calcula las afinidades basadas en hobbies entre dos personas (pasadas como struct del tipo persona)
int CalculaAfinitatHobbies (persona o, persona d)
{
	int afinidad=0;
	afinidad=abs((o.cine+o.musica)-(d.cine+d.musica));
	return afinidad;
}

// Calcula las afinidades basadas en hobbies entre dos personas (pasadas como struct del tipo persona)
int CalculaAfinidadHobbies (persona o, persona d)
{
	int afinidad=0;
	afinidad=abs((o.cine+o.musica)-(d.cine+d.musica));
	return afinidad;
}

// Calcula la puntuacio per a la busqueda multicriteri

double CalculaPuntuacio(int dm,int afinidad, int sexe, int diferenciaEdat, int fmDistancia,int fmHobbies,int fmSexe,int fmEdat)
{
	// La formula que hem emprat es:
	// Puntuacio=(1/distancia)*fmDistancia + (1/Hobbies)*fmHobbies + (1/edat)*fmEdat +sexe*fmsexe
	
	dm=abs(dm);
	if(dm==0) dm=1; // per evitar la divisio per 1
	if(afinidad==0) afinidad=1;
	if(diferenciaEdat==0) diferenciaEdat=1;
	double puntuacio=0;
	double inversadm=(float)1/dm;
	double inversaafinidad=(float)1/afinidad;
	double inversadiferenciaedat=(float)1/diferenciaEdat;

	puntuacio=(inversadm)*fmDistancia + (inversaafinidad)*fmHobbies+(inversadiferenciaedat)*fmEdat+sexe*fmSexe;
	return puntuacio;
}


// Una funcion utilizada para que en el menu principal solo se puedan introducir valores numéricos
int StringAEnter(string origen)
{
string cero="0";

if (origen.compare(cero)==0)
	return 0;
else {
	int enter=-1;
	enter=atoi(origen.c_str());
	// No es un valor entero, tenemos que devolver -1 para que el menú no salga
	if (enter == 0)
	enter = -1;
	return enter; 
     }
}


// Funció de lectura del fitxer.
/* La funció llegeix el fitxer i retorna el nombre de fitxes (usuaris) llegides */
int LlegirFitxer (ifstream &f, persona vector[TAM])
{
	int i = 0;
	cin.ignore(); 
	while(!f.eof() && i < TAM) //Mentre el fitxer no finalitze i siga menor que el tamany definit
	{
		
		getline(f, vector[i].nom);
		if(vector[i].nom.compare("")==0)
			return i;
		getline(f, vector[i].correu);
		f >> vector[i].latitud; 
		f.ignore(); 
		f >> vector[i].longitud;
		f.ignore(); 
		f >> vector[i].any;
		f.ignore();
		f >> vector[i].sexe;
        f.ignore();	
		f >> vector[i].musica;
		f.ignore();
		f >> vector[i].cine;
		f.ignore();
		i++; 
	}
	return i; 
}

// Funció (un booleà) per comprovar si el email ja existeix
bool CercaCorreu(string correu, persona vector[], int total)
{
	int i;
	for (i = 0; i <= total; i++)
	{
		if(correu == vector[i].correu)
		{
			return true;
		}
	}
	return false;
}

// Funció que troba la posició de la persona desitjada
int PosicioCorreu(string correu, persona vector[], int total)
{
	int i;
	if(correu == " ") 
	{
		return -1;
	}
	for (i = 0; i <= total; i++)
	{
		if(correu == vector[i].correu)
		{
			return i;
		}
	}
	return -1;
}

// Procediment d'ordenació de fitxes
void OrdenaFitxes(persona vector[], int total)
{
	int i, j;
	persona FitxaAuxiliar; // Utilitzem una estructura auxiliar per intercanviar posicions, com varem fer amb nombres per ordenarlos
	for (i = 0; i < total; i++)
	{
		for (j = 1; j < total; j++)
		{
			if (vector[j - 1].nom > vector[j].nom)
			{
				FitxaAuxiliar = vector[j - 1];
				vector[j - 1] = vector[j];
				vector[j] = FitxaAuxiliar;
			}
		}
	}
}

// Procediment que llista les fitxes 
 void LlistarFitxes(persona vector[], int total)
{
	int i;
	cout << "Usuaris de Fis-Darling registrats: " << endl;
    cout << "---------------" << endl;
    for(i = 0; i < total; i++)
    {
		cout << vector[i].nom << endl;
		cout << vector[i].correu << endl;
		cout << vector[i].latitud << "\t" << vector[i].longitud << "\t" << vector[i].any << "\t" << vector[i].sexe <<endl;
		cout << vector[i].musica << "\t" << vector[i].cine << endl;
	}
} 

// Procediment de creació de fitxes
void CrearNovaFitxa(ifstream &f, persona vector[], int &total)
{
	string resposta;
	cout << "Anem a registrar un nou usuari: " << endl;
	cout << "---------------" << endl;
	persona NovaFitxa; //Creem una "Nova Fitxa" que es una estructura.
	cin.ignore();
	cout << "Introdueix el nom del usuari a registrar (Cognoms, Nom): " << endl;
	getline(cin, NovaFitxa.nom);
	cout << "Introdueix el correu de l'usuari: " << endl;
	getline(cin, NovaFitxa.correu);
	while(CercaCorreu(NovaFitxa.correu,vector,total)) //Si ja existeix el correu farà el bucle while, que seria un while(true) 
	{
		cout << "Ja existeix una persona amb eixe correu, vols afegirla realment?" << endl;
		cin >> resposta;
		if(resposta == "Si"|| resposta == "si") //Provant el programa he trobat que la majúscula podia resultar un problema
		{
			cin.ignore();
			cout << "Introdueix un nou e-mail per aquesta persona: " << endl;
			getline(cin,NovaFitxa.correu);
		}	
		else if(resposta == "No" || resposta == "no")
		{
			return;
		}
	}
	cout << "Introdueix la latitud en la que es troba: " << endl;
	cin >> NovaFitxa.latitud;
	cout << "Introdueix la longitud: " << endl;
	cin  >> NovaFitxa.longitud;
	cout << "Introdueix l'any de Naiximent: " << endl;
	cin >> NovaFitxa.any;
	cout << "Introdueix el sexe de l'usuari [Home = h / Dona = d]" << endl;
	cin >> NovaFitxa.sexe;
	cout << "Introdueix l'interés per la música de l'usuari [En una escala de l'1 al 5] " << endl;
	cin >> NovaFitxa.musica;
	cout << "Introdueix l'interés pel cinema [En una escala de l'1 al 5] " << endl;
	cin >> NovaFitxa.cine;	
    vector[total] = NovaFitxa; //Posem aquesta fitxa al vector
    total = total + 1; //Incrementem el nombre d'usuaris
}
// Procediment que posa el vector de les persones al fitxer "guardantlo"
void PosaFitxer(const char* fitxer, int total, persona vector[])
{
	ofstream g; //Nou fitxer d'eixida
	g.open(fitxer); // Apertura pare escritura
	if(g.fail())
		{
			cout << "Error obrint el fitxer.";
			system("pause");
		}
else
		{
			for(int i=0;i<total;i++)
			{
						
				g<<vector[i].nom<<"\n";
				g<<vector[i].correu<<"\n";
				g<<vector[i].latitud<<'\t'<<vector[i].longitud<<'\t'<<vector[i].any<<'\t'<<vector[i].sexe<<"\n";
				g<<vector[i].musica<<'\t'<<vector[i].cine<<"\n";
				
			}
		}
	
}


//Funcion utilizada para modificar una ficha
void ModificarFitxa(persona vector[],int &t)
{
	string email;
	int r=0;
	cin.ignore();
	
	system("cls");
	cout << "Modificar fitxa"<<endl;
	cout << "---------------"<<endl;
	cout << "Introduix el correu electronic de la persona a buscar:";
	
	getline(cin,email);
	r=PosicioCorreu(email,vector,t); // si existe ese correo, me devuelve en que posicion dentro del vector de personas, y si no -1
	
	if(r==-1)
		{
		cout << "No existeis una persona amb eixe correu."<<endl;
		system("pause");
		}
		
	else
		{
			int opcio;
			while(true)
			{
			cout << "Nom actual:"<<vector[r].nom<<endl;
			cout << "Correu:"<<vector[r].correu<<endl;
			cout << "Latitud:"<<vector[r].latitud<<endl;
			cout << "Longitud:"<<vector[r].longitud<<endl;
			cout << "Any de naiximent:"<<vector[r].any<<endl;
			cout << "Sexe:"<<vector[r].sexe<<endl;
			cout << "Interes per la música:"<<vector[r].musica<<endl;
			cout << "Interes per el cine:"<<vector[r].cine<<endl;
			cout<<endl;
			cout<<"Que vols modificar? (0-Sortir,1-Nom, 2-Correu, 3-Latitud, 4-Longitud, 5-Naiximent, 6-Sexe, 7-Musica,8-Cine):";
			cin >> opcio;
			
			switch(opcio)
			{
			
			case 0:
				return;
				break;
				
			case 1:
				system("cls");
				cout<<"Introdueix el nou nom:";
				cin.ignore(); // limpiar el buffer de entrada
				getline(cin,vector[r].nom);
				cout << "Has cambiat el nom."<<endl;
				break;
				
			case 2:
				system("cls");
				cout<<"Introdueix el nou correu:";
				cin.ignore();
				getline(cin,vector[r].correu);
				cout << "Has cambiat el correu."<<endl;
				break;
				
			case 3:
				system("cls");
				cout<<"Introdueix la nova latitud:";
				cin>>vector[r].latitud;
				cout << "Has cambiat la latitud."<<endl;
				break;
				
			case 4:
				system("cls");
				cout<<"Introdueix la nova longitud:";
				cin>>vector[r].longitud;
				cout << "Has cambiat la longitud."<<endl;
				break;

			case 5:
				system("cls");
				cout<<"Introdueix el nou any de naiximent:";
				cin>>vector[r].any;
				cout << "Has cambiat el any de naiximent."<<endl;
				break;	
			
			case 6:
			system("cls");
			cout<<"Introdueix el nou sexe:";
			cin>>vector[r].sexe;
			cout << "Has cambiat el sexe."<<endl;
			break;	
			
			case 7:
			system("cls");
			cout<<"Introdueix el nou interes per la musica:";
			cin>>vector[r].musica;
			cout << "Has cambiat el interes per la musica."<<endl;
			break;	
			
			case 8:
			system("cls");
			cout<<"Introdueix el nou interes per el cine:";
			cin>>vector[r].cine;
			cout << "Has cambiat el interes per el cine."<<endl;
			break;		
			} //fswitch
			
						
			} //fwhile
		} //felse
		
} //ffuncio

//Funcion utilizada para borrar ficha

void EliminarFitxa(persona vector[],int &t)
{
	string email;
	int r=0;
	cin.ignore();
	
	system("cls");
	cout << "Eliminar fitxa"<<endl;
	cout << "---------------"<<endl;
	cout << "Introduix el correu electronic de la persona a eliminar:";
	
	getline(cin,email);
	r=PosicioCorreu(email,vector,t);
	
	if(r==-1)
		
			cout << "No existeis una persona amb eixe correu."<<endl;
		
		
	else
		{ 
		int i=r;
		// hem de desplazar tot el vector una posicio endarrere
		for(i=r;i<t;i++) // Desde la posicion en la que lo he encontrado hasta el final muevo uno hacia atras
			vector[i]=vector[i+1];	
		vector[i].nom="";
		t--; // He eliminat una fitxa, restem 1 del total
		cout << "Fitxa eliminada"<<endl;
		}
cout<<endl;
cout<<"Nombre total de fitxes:";
cout << t	;
cout <<endl;
system("pause");

}



// Esta funcion es para evitar que las personas aparezcan dos veces
// tal y como esta realizado, el algoritmo calcula la distancia entre maria y juan, así como la distancia entre juan y maria, y duplica el resultado. 
// Esta funcion hace que si ya se ha calculado la distancia entre i-->j, no se calcule la distancia entre j-->i
bool JaCalculat(int i, int j, compatibilidad top5[])
{
	for(int p=0;p<5;p++)
		if(top5[p].i==i && top5[p].j==j)
			return true;

return false;
}


void MostraTopDistancia(persona tothom [], compatibilidad Top5[],int t)

{
	system ("cls");
	cout << "-------------------------------------"<<endl;
	cout << "Persones mes compatibles per distancia"<<endl;
	cout << "-------------------------------------"<<endl;

	for (int i=0;i<5;i++)
	{
		int indice1,indice2;
		indice1=Top5[i].i;
		indice2=Top5[i].j;
		cout << tothom[indice1].nom;
		cout << " y ";	
		cout << tothom[indice2].nom;
		cout << "--> Distancia entre ellos:"<< Top5[i].DistanciaManhattan;
		cout << endl;
	}
system("pause");
}

void MostraTopAfinitatHobbies(persona tothom [], compatibilidad Top5[],int t)

{
	system ("cls");
	cout << "-------------------------------------"<<endl;
	cout << "Persones mes compatibles per hobbies"<<endl;
	cout << "-------------------------------------"<<endl;

	for (int i=0;i<5;i++)
	{
		int indice1,indice2;
		indice1=Top5[i].i;
		indice2=Top5[i].j;
		cout << tothom[indice1].nom;
		cout << " y ";	
		cout << tothom[indice2].nom;
		cout << "--> Distancia entre ellos:"<< Top5[i].AfinidadHobbies;
		cout << endl;
	}
system("pause");
}


void MostraTopAfinitatMulti(persona tothom [], compatibilidad Top5[],int t)

{
	system ("cls");
	cout << "------------------------------------------"<<endl;
	cout << "Persones mes compatibles per multicriteri"<<endl;
	cout << "------------------------------------------"<<endl;

	for (int i=0;i<5;i++)
	{
		int indice1,indice2;
		indice1=Top5[i].i;
		indice2=Top5[i].j;
		cout << tothom[indice1].nom;
		cout << " y ";	
		cout << tothom[indice2].nom;
		cout << "--> puntuacion multicriterio:"<< Top5[i].pt;
		cout << endl;
	}
system("pause");
}


// Calcula les 5 mes a prop per proximitat y hobbies

void TopCinc(persona tothom[],int t, int mode) // si mode == 1 muestra proximitat, si es 2 muestra hobbies
{

	// Mode = 1, per proximitat
if(mode==1)
{
	system("cls");
	compatibilidad top5[5]; // Array de estructura persona, que contendrá los 5 primeros
	float dm;
	int contador,contador2,contador3=0;
	for (int i=0;i<t;i++)
				for(int j=0;j<t;j++) // Para todas las personas, con otras personas, calcula distancia

					if(i!=j && !JaCalculat(j,i,top5))
					{
					dm=CalculaManhattan(tothom[i],tothom[j]); // distancia de manhattan entre la pesona i, y j
					// Merece ser insertado en el Top 5?
					for (contador=0;contador<5;contador++) // El Top 5 solo contiene 5 elementos
					{
					if(dm<top5[contador].DistanciaManhattan) // Si, es un top 5
						{
							// contador contiene ahora el indice donde insertar el nuevo elemento
							compatibilidad nuevo[5]; // creamos un array denominado nuevo auxiliar

								
							for (contador2=0;contador2<=contador;contador2++) //  contador2 va a ir desde la primera posicion hasta una posicion antes de donde se va a insertar el nuevo valor
								nuevo[contador2]=top5[contador2];
							nuevo[contador].i=i; // Insertando el nuevo dm calculado en la posicion que le corresponde
							nuevo[contador].j=j;
							nuevo[contador].DistanciaManhattan=dm;
							contador++; // Incrementamos contador para que apunte a la siguiente posición despues de la recientemente insertada.
							// Ahora nuevo contiene todas las posiciones desde el inicio hasta el nuevo elemento insertado
							for (contador3=contador;contador3<5;contador3++) // contador3 contiene desde la siguiente posicion en la que hemos insertado hasta el final
								nuevo[contador3]=top5[contador3-1];
							// nuevo ahora tiene una copia correcta de top5 al que se le ha insertado el elemento que corresponde.
							
							// Hacemos que top 5 contenga el valor de nuevo
							for(int g=0;g<5;g++)
								top5[g]=nuevo[g];
							contador=5; // hemos acabado esta pasada
						}
					}		
				}
	MostraTopDistancia(tothom, top5,t);
} // fif mode==1

if(mode==2)
{
	system("cls");
	compatibilidad top5[5]; // Array de estructura persona, que contendrá los 5 primeros
	int afinitat=0;
	int contador,contador2,contador3=0;
	for (int i=0;i<t;i++)
				for(int j=0;j<t;j++) // Para todas las personas, con otras personas, calcula distancia basada en hobbies

					if(i!=j && !JaCalculat(j,i,top5))
					{
					afinitat=CalculaAfinitatHobbies(tothom[i],tothom[j]); // distancia de manhattan entre la pesona i, y j
					// Merece ser insertado en el Top 5?
					for (contador=0;contador<5;contador++) // El Top 5 solo contiene 5 elementos
					{
					if(afinitat<top5[contador].AfinidadHobbies) // Si, es un top 5 por hobbies
						{
							// contador contiene ahora el indice donde insertar el nuevo elemento
							compatibilidad nuevo[5]; // creamos un array denominado nuevo auxiliar

								
							for (contador2=0;contador2<=contador;contador2++) //  contador2 va a ir desde la primera posicion hasta una posicion antes de donde se va a insertar el nuevo valor
								nuevo[contador2]=top5[contador2];
							nuevo[contador].i=i; // Insertando el nuevo dm calculado en la posicion que le corresponde
							nuevo[contador].j=j;
							nuevo[contador].AfinidadHobbies=afinitat;
							contador++; // Incrementamos contador para que apunte a la siguiente posición despues de la recientemente insertada.
							// Ahora nuevo contiene todas las posiciones desde el inicio hasta el nuevo elemento insertado
							for (contador3=contador;contador3<5;contador3++) // contador3 contiene desde la siguiente posicion en la que hemos insertado hasta el final
								nuevo[contador3]=top5[contador3-1];
							// nuevo ahora tiene una copia correcta de top5 al que se le ha insertado el elemento que corresponde.
							
							// Hacemos que top 5 contenga el valor de nuevo
							for(int g=0;g<5;g++)
								top5[g]=nuevo[g];
							contador=5; // hemos acabado esta pasada
						}
					}		
				}
	MostraTopAfinitatHobbies(tothom, top5,t);
} // fif mode==2
}

void TopCincMulticriteri(persona tothom[],int t, int fmDistancia, int fmHobbies,int fmSexe, int fmEdat)
{
system("cls");
	compatibilidad top5[5]; // Array de estructura persona, que contendrá los 5 primeros
	float dm;
	int afinitat=0;
	int diferenciaEdat=0;
	int diferenciaSexe=0;
	double pt=0; // puntacio total multicriteri
	int contador,contador2,contador3=0;
	for (int i=0;i<t;i++)
				for(int j=0;j<t;j++) // Para todas las personas, con otras personas, calcula distancia

					if(i!=j && !JaCalculat(j,i,top5))
					{
					dm=CalculaManhattan(tothom[i],tothom[j]); 
					afinitat=CalculaAfinitatHobbies(tothom[i],tothom[j]); // distancia de manhattan entre la pesona i, y j
					diferenciaEdat=abs(tothom[i].any-tothom[j].any);
					if(tothom[i].sexe==tothom[j].sexe)
						diferenciaSexe=-1;
					else if (tothom[i].sexe!=tothom[j].sexe)
							diferenciaSexe=1;
				
					pt=CalculaPuntuacio(dm,afinitat, diferenciaSexe, diferenciaEdat,fmDistancia, fmHobbies,fmSexe,fmEdat);
					
					// Merece ser insertado en el Top 5?
					for (contador=0;contador<5;contador++) // El Top 5 solo contiene 5 elementos
					{
					if(pt>top5[contador].pt) // ordenacio de major a menor
						{
							// contador contiene ahora el indice donde insertar el nuevo elemento
							compatibilidad nuevo[5]; // creamos un array denominado nuevo auxiliar

							//if(contador==0) // Insercion al principio
								
							for (contador2=0;contador2<=contador;contador2++) //  contador2 va a ir desde la primera posicion hasta una posicion antes de donde se va a insertar el nuevo valor
								nuevo[contador2]=top5[contador2];
							nuevo[contador].i=i; // Insertando el nuevo dm calculado en la posicion que le corresponde
							nuevo[contador].j=j;
							nuevo[contador].pt=pt;
							contador++; // Incrementamos contador para que apunte a la siguiente posición despues de la recientemente insertada.
							// Ahora nuevo contiene todas las posiciones desde el inicio hasta el nuevo elemento insertado
							for (contador3=contador;contador3<5;contador3++) // contador3 contiene desde la siguiente posicion en la que hemos insertado hasta el final
								nuevo[contador3]=top5[contador3-1];
							// nuevo ahora tiene una copia correcta de top5 al que se le ha insertado el elemento que corresponde.
							
							// Hacemos que top 5 contenga el valor de nuevo
							for(int g=0;g<5;g++)
								top5[g]=nuevo[g];
							contador=5; // hemos acabado esta pasada
						}
					}		
				}
	MostraTopAfinitatMulti(tothom, top5,t);
} 

 

//donats els multiplicadors et dona el Top 5 persones més afins
void Multicriteri(persona tothom[],int t)
{
	system("cls");
	int fmDistancia=0; // Factor multiplicador distancia
	int fmHobbies=0; // factor multiplicador hobbies
	int fmSexe=0;  // factor multiplicador sexo
	int fmEdat=0; // factor multiplicador edad

	// Vamos a asignar una puntuacion total a cada par de personas, cuanto mayor sea esa puntuacion, mas afinidad
	// PT=(1/distancia)+fmDistancia + (1/Hobbies)+fmHobbies + (1/edat)+fmEdat + (1/sexe)+sexe

	system("cls");

	cout << "Introdueix factor multiplicador distancia (-100 a + 100 ):";
	cin >> fmDistancia;

	cout << "Introdueix factor multiplicador per als hobbies (-100 a + 100 ):";
	cin >> fmHobbies;
		
	cout << "Introdueix factor multiplicador per la edat (-100 a + 100 ):";
	cin >> fmEdat;


	cout << "Introdueix factor multiplicador per el sexe (-100 a + 100):";
	cin >> fmSexe;	

		
TopCincMulticriteri(tothom,t, fmDistancia,fmHobbies,fmSexe,fmEdat);
		

}

float RandomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

void FitxerProba(char nomFitxer[], int cuants)
{
	ofstream fitxer;
	fitxer.open(nomFitxer);
	if(!fitxer)
		return;	
	string nomaleatori;
	string cognomaleatori1;
	string cognomaleatori2;
	string noms[]={"ANTONIO","JOSE","MANUEL","FRANCISCO","JUAN","DAVID","JOSE ANTONIO","JOSE LUIS","JAVIER","GONZALO","JESUS","FRANCISCO JAVIER","CARLOS","DANIEL","Camila","Nicole","Itzel","Josefina","Emily","Melany","Kiara","Evelyn","Vanessa","Michelle","Giuliana","Luciana","Aylin","Yesenia","Mayerly"};
	string cognoms[]={"Garcia","Lopez","Perez","Gonzalez","Sanchez","Martinez","Rodriguez","Fernandez","Gomez","Martin","Hernandez","Ruiz","Diaz","Moreno","Ramos"};
	//int temp=system("timer dir)");
	//srand(temp);
	
	for (int i=0;i<cuants;i++)
	{
	
	int r1 = rand() % 29;
	int r2 = rand () % 14;
	int r3 = rand () % 14;
	int any=rand () % 2000;
	int musica=rand () % 6;
	int cine=rand () % 6;
	char sexe;
	if(i%2) // paritat de homes i dones
			sexe='d';
	else
			sexe='h';

	float latitud=RandomFloat (-90,90);
	float longitud=RandomFloat (-180,180);
	 
	
	nomaleatori=noms[r1];
	cognomaleatori1=cognoms[r2].c_str();
	cognomaleatori2=cognoms[r3].c_str();
	
    fitxer <<cognomaleatori1<<" "<<cognomaleatori2<<","<<" "<<nomaleatori<<endl;
	fitxer << nomaleatori<<cognomaleatori1<<"."<<cognomaleatori2<<"@"<<"gmail.com"<<endl;
	fitxer << latitud<<"\t"<<longitud<<"\t"<<any<<"\t"<<sexe<<endl;
	fitxer << musica <<"\t"<<cine<<endl;
	
	}

	
	fitxer.close();
	cout << "Hem generat el fitxer:"<<nomFitxer<<endl;
	
}

//Programa Principal
int main()
{
	string n;
	int p=-1; // para no salir del menu principal
	int t;
	char a;
	persona vector[TAM]; // vector es el vector que contiene las personas leídas dle fichero
	ifstream f; 
	string nom;
		system("cls");
		cout << "Benvingut/da a Fis-Darling! La millor xarxa per trobar parella."<< "(Recomenada per Einstein, Newton i Planck.)" << endl;
		cout << "Introdueix el nom del fitxer on estan els usuaris de Fis-Darling:";
		cin >> nom;
		f.open(nom.c_str());
		if(f.fail()) // Si al intentar abrir el fichero falla no existe el nombre de ese fichero, el enunciado de la práctica indica que se abra un fichero nuevo
		{
		cout << "Xarxa social nova."<<endl;
		cout << "No tenim persones registrades actualment." << endl;
		system("pause");
		}
	else
		t=LlegirFitxer(f, vector); // pasando el fichero (f) y el vector que contendrá las personas
		// Menu principal
		while(p==-1) // para que no salga del menu hasta que no pongas la opcion 0, solo la opcion de salir (opcion  pone p!=-1 y entonces el bucle sale)
		{
		system("cls");
		cout << "Elegeix la opcio desitjada: " << endl;
		cout << "0.Eixir\n" << "1.Crear nova fitxa\n" << "2.Llistar fitxes\n";
		cout << "3.Modificar les dades d'una determinada fitxa\n";
		cout << "4.Esborrar una fitxa" << endl;
		cout << "5.Cercar persones\n" << "\ta)Top 5 Persones mes prop.\n" << "\tb)Top 5 Persones amb interessos comuns cine i musica."<<"\n";
		cout << "6.Cercador multicriteri" << endl;		 
		cout << "7.Crear un fitxer de proba per a probar(opcional)" << endl;	
		cout << "Opcio:";
		cin >> n;
		p=StringAEnter(n);
		
		switch (p)
		{
			case 0: // salir
				char resposta; // para guardar si realmente quiere salir
				resposta='p';
				while(resposta!='S' && resposta!='s' && resposta!='n' && resposta!='N')
				{
				cout << "Desitja conservar conservar el canvis? (S/N):";
				cin >> resposta;
				}
				
				if(resposta=='S' || resposta=='s')
						{
						OrdenaFitxes(vector,t); // Ordena el vector de personas antes de guardar
						PosaFitxer(nom.c_str(),t,vector); // c_str convierte un string a char, le paso el nombre como char, el tamaño y el vector de personas a escribir en el fichero
						}
			break;
				
			case 1: // crear nueva ficha

				CrearNovaFitxa(f, vector,t); // f=fichero, vector = vector de personas, t numero de personas
				cout<<"Nova Fitxa insertada";
				OrdenaFitxes(vector,t);
				//LlistarFitxes(vector,t);				
				p=-1;
				break;
				
			case 2:	
				system("cls");
				OrdenaFitxes(vector,t);
				LlistarFitxes(vector,t);
				p=-1;
				system("pause");
				break;	
			case 3:
				ModificarFitxa(vector,t);
				p=-1;
				break;
				
			case 4:
				EliminarFitxa(vector,t);
				p=-1;
				break;
			
						
			case 5:
				cout << "Subopcio a,b?";
				cin >> a;
				if (a=='a')
				{

					if(t<=1)
						{
						cout << "No hi ha ninguna persona, o hi ha sols una persona en la BBDD."<<endl;
						cout << "No podem calcular compatibilitats."<<endl;
						system("pause");
						p=-1;
						}
					else 
						{
						// si hi ha menys de 5 persones mostren un warning pero calculem
						if (t<6)
							{		
							cout << "Sols hi ha "<<t << " persones en la BBDD." << endl <<"Mostrant la afinitat dels que hi ha fins ara.\b"<<endl<<endl;
							TopCinc(vector,t,t);
							p=-1;
							break;
							}
						// De lo contrari mostren les 5 primeres
						//TopProp(vector,t,5);
						TopCinc(vector,t,1);
						
						}
					}

					if(a=='b')
					{

						if(t<=1)
						{
						cout << "No hi ha ninguna persona, o hi ha sols una persona en la BBDD."<<endl;
						cout << "No podem calcular compatibilitats."<<endl;
						system("pause");
						}
					else 
						{
						// si hi ha menys de 5 persones mostren un warning pero calculem
						if (t<6)
							{		
							cout << "Sols hi ha "<<t << " persones en la BBDD." << endl <<"Mostrant la afinitat dels que hi ha fins ara.\b"<<endl<<endl;
							TopCinc(vector,t,2);
							p=-1;
							break;
							}
						}
						// De lo contrari mostren les 5 primeres
						TopCinc(vector,t,2);
							p=-1;
							break;
					} 
						
				p=-1;
				break;

				case 6:
				Multicriteri(vector,t);
				system("pause");
				p=-1;
				break;

				case 7:
				
				char nomFitxer[100];
				int cuants;
				char res;
				system("cls");
				cout << "-------------------------------------"<<endl;
				cout << "Fitxer de proba per a testear		  "<<endl;
				cout << "-------------------------------------"<<endl;

				cout << "Nom del fitxer:";
				cin >> nomFitxer;
				cout << endl;
				cout << "Cuants registres vols en el fitxer:";
				cin >> cuants;
				FitxerProba(nomFitxer, cuants);
				cout<<endl;
				cout << "Vols cargar el nou fitxer en memoria?(s/n)";
				cin >> res;
				if(res=='s' || res=='S')
					{	
					ifstream ff;
					ff.open(nomFitxer);
					t=LlegirFitxer(ff, vector);
					p=-1;
					}
										
				break;		
			
		} //fswitch
	} //fwhile	
	f.close();
	system("pause");
	return 0;

} //fmain

