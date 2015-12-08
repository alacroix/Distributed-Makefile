# distributed-makefile
Distributed Makefile with MPI + OpenMP

Extra external libraries used : Boost, OpenMP, MPI

#Connexion grid sur le site de Grenoble
ssh login@access.grenoble.grid5000.fr

#Réservation des noeuds
oarsub -I -l nodes=5,walltime=5:00 -t deploy

#Déploiement de l'environnement
kadeploy3 -f $OAR_NODE_FILE -e jessie-x64-big -k

#Install findBoost sur tous les  noeuds
apt-get install libboost-mpi-dev
apt-get install libboost-filesystem-dev
apt-get install sshpass
mkdir distributed-makefile && cd distributed-makefile
mkdir out
passwd root
#Mettre "admin" en mot de passe

#Sur le master
#Configuration pour la connexion au net et clone
export http_proxy=http://proxy:3128/ && export https_proxy=http://proxy:3128/
git clone https://github.com/alacroix/distributed-makefile.git && cd distributed-makefile && git checkout iteratif_boostmpi && cmake CMakeLists.txt && make

#Sur le master - creation d'une clé ssh
ssh-keygen -t dsa

#Sur le frontend de Grenoble, on recupere la clé publique générée
scp root@genepi-4:.ssh/id_dsa.pub authorized_keys2

#Sur tous les noeuds esclaves on recopie cette clé
scp authorized_keys2 root@genepi-54:.ssh/


#On envoie la liste des noeuds au master
uniq $OAR_NODEFILE > mpi_hostfiles
scp mpi_hostfiles root@genepi-4:

#Depuis le master on copie l'executable sur tous les fils
scp distributed-makefile/out/distributed_makefile root@genepi-15:distributed-makefile/out/distributed_makefile

#Connection sur le master et execution du mpi (répondre "yes" aux connections)
ssh root@genepi-4
mpirun -np 5 --hostfile mpi_hostfiles distributed-makefile/out/distributed_makefile distributed-makefile/test/premier/Makefile-small