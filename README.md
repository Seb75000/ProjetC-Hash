# ProjetC-Hash

Le programme ProjetC-Hash permet de créer des rainbow tables et les interroger.


# Prérequis

## Des outils de compilation

Sur Debian ou ubuntu, vous pouvez les installer avec la commande **apt install build-essential**

## Librairies OpenSSL

Pour compiler le programme vous devez avoir les librairies OpenSSL installées. Sur Debian ou ubuntu, vous pouvez les installer avec la commande **sudo apt install libssl-dev**


# Installation

Synchronisez le git en local sur votre environnement, et exécutez la commande **make** dans le répertoire. Si tout se passe bien, un fichier exécutable est apparu dans le sous répertoire *"bin"*.


# Utilisation

L'application permet 2 modes de fonctionnement :
 - La génération d'une table de hashage
 - La recherche dans une table de hashage (Lookup)

## Génération
Le 1er mode s'appelle avec l'option "-G", et permet de prendre un dictionnaire comme fichier d'entrée, de générer un hash de chaque entrée de ce dictionnaire, et mettre le hash et le clair dans un fichier de sortie.

Exemple d'utilisation : vous avez un fichier dictionnaire rockyou.txt, vous allez générer un fichier rainbow.txt pour l'algorithme sha1
*hasheur.exe -G /path/to/rockyou.txt /path/to/rainbow.txt -a sha1*

Selon les performances de l'ordinateur sur lequel le programme est exécuté et l'algorithme choisi, il faut compter environ 1 minute pour 10 millions de lignes d'entrée.

## Lookup
Le 2e mode s'appelle avec l'option "-L", et permet passer des hash par l'entrée standard, et de les rechercher dans le fichier dont le nom est passé en paramètre. Les hash dont les antécédants sont trouvés sortent par la sortie standard.
Le programme va parcourir le fichier de hash et le monter en mémoire, puis faire la recherche des hashs passés en entrée standard.

Exemple d'utilisation : vous avez le fichier rainbow.txt qui contient les hash / clairs, et un fichier hash.txt qui contient les hash pour lesquels on cherche les clairs 
*cat hash.txt | hasheur.exe -L /path/to/rainbow.txt*

Selon les performances de l'ordinateur sur lequel le programme est exécuté, il faut compter environ 1 minute pour mettre en mémoire 15 millions de lignes d'entrée, puis la recherche est quasi instantanée.
Pour chaque hash recherché, la sortie standard indiquera si le clair a été trouvé ou non.

# Formatage des fichiers

## Le fichier dictionnaire

Le fichier doit être formatté de la façon suivante : 
  - les entrées sont séparées par une fin de ligne
  - les fins de ligne sont au format "\n"
  
## Le fichier de relation hash-clair

Le fichier est généré de la façon suivante :
  - Chaque ligne est composée de 2 champs, un hash, et un clair, séparés par un caractère de tabulation. Toute autre tabulation fera partie du clair
  - Les fins de ligne sont au format "\n"
  - Les hash peuvent être mixtes (un même fichier peut avoir des hashs md5, sha1 etc)
  - Si le programme utilise un fichier pré-existant, les couples hash-clair calculés sont ajoutés à la fin du fichier existant.


# Help !
Génération de la hashtable à partir du dictionnaire :
        hasheur.exe -G <fichier_dictionnaire> <fichier_hashtable> (-a ALGO)
         <fichier_dictionnaire> : fichier contenant les mots à hasher
         <fichier_hashtable> : fichier de sortie contenant les hashs et les mots en clair. Si le fichier existe déjà, les hashs seront ajoutés à la suite, même si d'algorithme différent.
         -a ALGO : algorithme de hachage à utiliser (facultatif. Par défaut, sha256 sera utilisé)
        Algorithmes de hachage supportés : celles de la librairie OpenSSL
                Exemples : sha1, sha256, md5...

Recherche de hashs dans la hashtable :
        cat MesHash | hasheur.exe -L <fichier_hastable>
         <fichier_hastable> : fichier contenant les hashs et les mots en clair, avec "\n" comme séparateur de ligne.

Affichage de l'aide :
        hasheur.exe -H
