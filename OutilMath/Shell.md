# TD2 Exercice shell -awk-C

## Exo1 : Shell

    A = 'echo *'
    echo '$A' //les apostrophes bloquents les substitutions donc ça affiche : $A

    echo "$A" //Les guillemets bloquent les substitutions de chemin donc ça affiche : echo *

    echo $A //Les substitutions de variables se fait en priorité, donc : echo fich1, fich2, ...

    $A //Liste des fichiers du répertoire courant.

## Exo2 : Bilan sur un fichier

    #/bin/sh
    set 'ls -il $1'
    echo nomfichier : ${10}
    echo num inoeud : $1
    echo nom propriétaire : $5
    echo nomgroupe : $jesaispas
    echo taille : $9
    echo nblien : $3

## Exo3 : Répertoire courant

1. nf : nombre de fichier du repertoire courant  
`$ fich * | grep -v Directory|wc -l`

2. ra : oui si repertoire courant == repertoire d'acceuil, non sinon  
`test 'pwd' == $HOME && echo oui || echo non`

3. prc : Profondeur du répertoire courant  
`pwd | tr'/'''|wc -c`

4. ouest : affiche le repertoire de l'utilisateur donnée en parametre sinon dire que l'utilisateur n'existe pas.  
`$ouest Martin`  
NOM = $1  
`finger $NOM>tmp 2>/dev/null`  
`grep login tmp && 'grep Directory tmp' && ` /* echo $NOM est dans le rep $1 OU echo $NOM n'existe pas fans le systeme*/

## Exo4 En tête programme C

    prog.h =>
    void affiche(char* str){
        int calcProduit(int* t,int n)
    }

    $ifdef prog.h
    #ifndef PROG.H
    #define PROG.H
        val affiche(char* str)
        val calcProd(int *t, int n)
    #endif /*PROG.H*/



    #!/bin/sh
    FIC = $1
    ITS = .  //Separateur ($1 => avant le point ; $2 => apres le point.s)
    set $1
    NOM = 'echo $1 | tr '[a-z]' '[A-Z]''
    echo "#ifndef ${NOM}_H" > tmp
    echo "#define ${NOM}_H" >> tmp
    cat $FIC >> tmp //tester si le fichier existe, rajouter devant : test -f $FIC &&
    echo "#endif /* ${NOM}_H */" >> tmp
    mv tmp $FIC

## Exo5 Arborescence

    #!/bin/sh
    FICNOM = $1
    FICPDF = $2
    while read NOM PRENOM
    do
        Dir = 'echo $NOM$PRENOM | tr -d`'|tr '[:lower]''[:upper:]'`
        mkdir $Dir
        cp f.pdf $Dir
        LISTREP = $Dir $LISTREP
    done < $FICNOM
    tar -cvf structureRep.tar $LISTREP && echo ArchiveRealise avec succes

---

Script shell => vérifier que chaque rep S1 ne contient que des fichiers sujet1.dot chaque rep S2 ne contient que des fichiers sujet2.dot

burname = '/home/user/Paul/Rep/doc3.txt' => doc3.txt  
dirname = '/home/user/Paul/Rep/doc3.txt' => /home/user/Paul 

    #!bin/sh
    FICNOM = $1
    FICDOT = $2

cmde1 ; cmde2 ; cmde3 => s'executent quelque soit la valeur retourné pas la cmde précédente.  
cmde1 && cmde2 && cmde3 => s'executent si la valeur retourné par la cmde précédente est VRAI  
cmde1 || cmde2 || cmde3 => s'executent si la valeur retourné par la cmde précédente est FAUX

Chemin d'acces au repertoire 'EXAMEN' : `/home/user/Dep/L3/EXAMEN`

`basename /home/user/Dep/L3/toto.txt` => retourne 'toto.txt' il retourne le nom du fichier ou du répertoire qui se trouve après le dernier /.  
`dirname /home/user/Dep/L3/toto.txt` => retourne tout ce qui se trouve avant le dernier /. Ici => /home/user/Dep/L3

    #!/bin/bash
    REPEXAM = $1
    for i in 1 2
    do
        for f in $REPEXAM/GROUPE[A-G]/Sujet[1-2]/*/*
        do
            test `basename $f` = Sujet$i.odt || echo rep `dirname $f`
        done
    done

---

Renommer chaque fichier sous la forme :  
GroupeX_nom_SujetY.odt   avec Y = 1 ou 2 et X = A ou B ou ... ou G

    #!/bin/bash
    REPEXAM = $1
    cd $REPEXAM
    for r in A B C D E F G
    do
        for i in 1 2
        do
            for dir in Groupe$g/Sujet$i/*
            do
                nom = `basename $dir`
                nomFich = Groupe$g'_'$nom'_'Sujet$i.odt
                mv $dir/Sujet$i.odt $dir/$NOMFICH
            done
        done
    done

---

- Creer SUJET1 et SUJET2  
- Copier tous les fichiers Sujet1.odt dans SUJET1
- Copier tous les fichiers Sujet2.odt dans SUJET2

voici

    #!/bin/bash
    REPEXAM = $1
    cd $REPEXAM
    mkdir SUJET1 SUJET2
    for i in 1 2
    do
        cp Groupe[A-G]/Sujet$i/*/*.odt Sujet$i
    done

---

## EXO6 AWK

1. Affiche les 2 premiers champs de chaque ligne en ordre inverse.

2. Affiche toutes les lignes du fichier dont le 1er champs est différent du 1er champs de la ligne précédente.

---

## EXO7

1. Champs séparés par ',' ; ' \t' ; '\t '  
afficher les 2 premiers champs en ordre inversé

<\br>

    BEGIN{FS=",[ \t]*|[\t ]+" ; OFS="\t"}  
    {print $2,$1}

2. La somme et la moyenne du 1er champs

<\br>

    Begin{Somme = 0}
         {Somme += $1}
    END {print Somme, Somme/NR}

3. Toutes les lignes entre "start" et "stop"

<\br>

    /start/,/stop/ {print;}

4. Toutes les lignes plus longues que 72 caractères

length( chaine de caractere) => longueur de la chaine.  
$0 -> une variable contenant toute la ligne courante

    length($0)>72{print;}

5. Tous les champs de chaque ligne en ordre inverse.  
NF <- contient le nombre de champs de la ligne courante   
=> traverser tous les champs en les concatenant dans l'ordre inverse, dans une chaine de caractere, où à la fin de la boucle on affiche la chaine de caractère obtenue.  

<\br>

    {lig=" ";for(i=1;i<NF;i++) lig=$i" "lig; print lig}

---

## EXO8

Tester que toutes les lignes ont le même nombre d'éléments.

    BEGIN{readline ; nb=NF ; Res = true ;}
    NF!=nb{Res=false;}
    END{if(Res==true) print"oui" ; else print"Nom";}

2 / 

    BEGIN{No=1}
    {$2 = no++}
    {print}

---

## EXO 9

1.

    BEGIN{nli = 0}
    ($2!=0 && $3!=0){print("La ligne %d est incohérente",NR); nli++;}
    END{if(nli==0)printf("Fichier coherent");
    else Print("vous avez %d lignes incohérente dans votre fichier",nli);}

2.

    BEGIN{totalDep=0,totalRen=0; Decouvert=0;}
    {totalDep+=$2; totalRen+=$3;
    if(totalDep > totalRen && Decouvert==0){
    dateDebut=$1; Decouvert = 1;}
    if(totalRen>=totalDep && Decouvert ==1){
        DateFin=$1; Decouvert=0;
    }
    print("Periode de decouvert du %s au %s\n", dateDebut,DateFin);
    }
    END{print("total des depenses %d\n", totalDep);
    print("total des Rentrees %d\n", totalRen);}

---

## EXO 10

Soit Cours.tex un fichier Latex contenant la descritpion d'un cours.  
=> {generer le fichier Cours.pdf à partir de Cours.tex  
generer le fichier Cours2.pdf contenant la description du cours sous la forme de 2 pages par page}

<u>Etapes :</u> Pour fabriquer Cours.pdf :  
- On fabrique le fichier Cours.pdf à partir de Cours.ps en untilisant le code : `ps2pdf`  
$ps2pdf Cours.ps => Cours.pdf

- On doit fabriquer Cours2.ps à partir de Cours.ps avec le code : `psnup`  
$psnup -n Cours.ps > Cours2.ps

- On fabrique le fichier Cours.ps à partir de Cours.dvi avec le code : `dvips`  
$dvips -o Cours.ps Cours.dvi => Cours.ps

- On fabrique Cours.dvi à partir du fichier latex  
$latex Cours.tex => Cours.dvi

1. Donner un ou plusieurs codes shell permettant de fabriquer Cours3.pdf à partir de Cours.ps  

psnup -n 2 Cours.ps > Cours2.ps; ps2pdf Cours2.ps => Cours2.pdf  
psnup -n 2 Cours.ps | ps2.pdf - > Cours2.pdf  

2. Donner le graphes de dependance pour Cours.pdf et Cours2.pdf  
![](grapheDepPDF.png "Graphe Des dépendances")

3. 
- Date de derniere mise à jour par tous les fichiers est 1
- Le fichier Cours.ps a été effacé => date = -infini  
=> Retracer le graphe des dépendance ![](grapheDepPDFDateMiseJour.png)

4. Donnez le tri topologique associé aux cibles Cours.pdf et Cours2.pdf

Cours.pdf : Cours.ps  
Cours2.pdf : Cours.ps, Cours2.ps  
Cours.pdf, Cours2.pdf : Cours.ps, Cours2.ps  

5. Quelles sont les commandes executées par make pour fabriquer Cours2.pdf en partant du graphe actualisé.

dvi2ps -o Cours.ps Cours.dvi  
psnup -n 2 Cours.ps > Cours2.ps  
ps2pdf Cours2.ps

6. Ecrire le makefile pour generer Cours.pdf et Cours2.pdf

Cours.dvi : Cours.tex  ->  Latex Cours.tex  
Cours.ps : Cours.dvi  ->  dvips -o Cours.ps Cours.dvi  
Cours2.ps : Cours.ps  ->  psnup -n 2 Cours.ps > Cours2.ps  
Cours.pdf : Cours.ps  -> ps2pdf Cours.ps  
Cours2.pdf : Cours2.ps  ->  ps2pdf Cours2.ps

7. Makefile avec variables et regles implicites

Rappel : hello.o : hello.c hello.h main.c

\$@ -> La cible, donc hello.o  
\$< -> la premiere dependance, donc hello.c  
\$^ -> toutes les dependances, donc hello.c hello.h main.c

    NBP = 2
    %.dvi:%.tex
    -> latex $<

    %($NBP).ps:%.ps
    -> psnup $< >$@

    %.ps:%.dvi
    -> dvips -o $@ $<

    %.pdf:%.ps
    -> ps2pdf $<

---

## Exo11

1. ![](grapheDepPDF_Exo11.png)

Suite de code pour obtenir essai.i:
- a2b essai.a essai.b
- c2d essai.c essai.d
- e2f essai.e essai.f
- bd2g essai.b essai.d essai.g
- df2h essai.f essai.d essai.h
- gh2i essai.g essai.h essai.i

2. Le makefile

<br\>

    %.b:%.a
    ->a2b $< $@ //$< = essai.a && $@ = essai.b

    %.d:%.c
    -> c2d $< $@

    %.f:%.e
    ->e2f $< $@

    %.g:%.b%.d
    ->gb2d $^ $@
    
    %.e:%.f%.h
    ->ef2h $^ $@
    
    %.i:%.g%.h
    ->gh2i $^ $@
    
3. `$make essai.i` pour créer essai.i make lancera les commandes pour generer les fichiers de dependances intermédiaires => donc toutes les commandes seront executées.

4. Si essai.c est modifié :  
`$make essai.i`
make detecte le changement dans essai.c et generera essai.d, puis essai.g, puis essai.i