# distributed-makefile
Distributed Makefile with MPI + OpenMP

Extra external libraries used : Boost, OpenMP, MPI

##Préparation de l'environnement
#####Connexion grid sur le site de Grenoble
ssh login@access.grenoble.grid5000.fr

#####Réservation des noeuds
oarsub -I -l nodes=5,walltime=5:00 -t deploy

#####Déploiement de l'environnement
kadeploy3 -f $OAR_NODE_FILE -e jessie-x64-big -k

#####Installation de findBoost sur tous les  noeuds
- apt-get install libboost-mpi-dev
- apt-get install libboost-filesystem-dev
- apt-get install sshpass
- mkdir distributed-makefile && cd distributed-makefile
- mkdir out
- passwd root
Mettre "admin" en mot de passe


##Configuration du réseau
#####Configuration pour la connexion au network et clone : sur master
- export http_proxy=http://proxy:3128/ && export https_proxy=http://proxy:3128/
- git clone https://github.com/alacroix/distributed-makefile.git && cd distributed-makefile && git checkout iteratif_boostmpi && cmake CMakeLists.txt && make

#####Sur le master - creation d'une clé ssh
- ssh-keygen -t dsa

#####Echange des clés ssh
Sur le frontend de Grenoble :
scp root@genepi-4:.ssh/id_dsa.pub authorized_keys2

Sur tous les noeuds esclaves :
scp authorized_keys2 root@genepi-54:.ssh/


##Installation du programme
#####Sur le frontend : envoi de la liste des noeuds au master
- uniq $OAR_NODEFILE > mpi_hostfiles
- scp mpi_hostfiles root@genepi-4:

#####Sur le master : envoi de l'executable sur tous les fils
scp distributed-makefile/out/distributed_makefile root@genepi-15:distributed-makefile/out/distributed_makefile

#Execution du makefile distribué
Connection sur le master et execution du mpi (répondre "yes" aux connections)
mpirun -np 5 --hostfile mpi_hostfiles distributed-makefile/out/distributed_makefile distributed-makefile/test/premier/Makefile-small