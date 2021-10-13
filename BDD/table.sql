DROP TABLE EMPLOYE;
DROP TABLE SERVICE;

CREATE TABLE SERVICE (
    SerNo integer PRIMARY KEY,
    Nom varchar(255) NOT NULL,
    Lieu varchar(255) NOT NULL
);

CREATE TABLE EMPLOYE (
    EmpNo integer PRIMARY KEY,
    Nom varchar(255) NOT NULL,
    Prenom varchar(255) NOT NULL,
    Fonction varchar(255) NOT NULL,
    Chef integer,
    DateEmbauche date NOT NULL,
    Salaire integer DEFAULT 0,
    Commission varchar(255),
    SerNo integer NOT NULL,
    CONSTRAINT UC_Person UNIQUE (Nom, Prenom),
    CONSTRAINT valeurs_permises_pour_fonction CHECK (Fonction in ('Président', 'Gérant', 'Secrétaire', 'Vendeur')),
    CONSTRAINT cle_etrangere FOREIGN KEY(SerNo) REFERENCES SERVICE(SerNo) ON DELETE CASCADE,
    CONSTRAINT chef_is_employe FOREIGN KEY(Chef) REFERENCES EMPLOYE(EmpNo)
);

INSERT INTO SERVICE VALUES (10, 'Comptabilité', 'Paris');
INSERT INTO SERVICE VALUES (20, 'Affaires Générales', 'Dijon');
INSERT INTO SERVICE VALUES (30, 'Ventes', 'Besançon');
INSERT INTO SERVICE VALUES (40, 'Ressources Humaines', 'Lyon');

INSERT INTO EMPLOYE VALUES (7839, 'Ramirez', 'Jules', 'Président', NULL, to_date('17/11/81', 'DD/MM/YY'), 5000.00, NULL, 30);
INSERT INTO EMPLOYE VALUES (7521, 'Dupuy', 'Maurice', 'Vendeur', 7839, to_date('22/09/80', 'DD/MM/YY'), 7000.00, 500.00, 30);
INSERT INTO EMPLOYE VALUES (7566, 'Deschamps', 'Jean', 'Gérant', 7839, to_date('02/04/81', 'DD/MM/YY'), 2975.00, NULL, 20);
INSERT INTO EMPLOYE VALUES (7902, 'Jamme', 'Michelle', 'Gérant', 7566, to_date('03/12/81', 'DD/MM/YY'), 3000.00, NULL, 20);
INSERT INTO EMPLOYE VALUES (7369, 'Dupont', 'Jean', 'Secrétaire', 7902, to_date('17/12/80', 'DD/MM/YY'), 800.00, NULL, 20);
INSERT INTO EMPLOYE VALUES (7788, 'Remond', 'Pierre', 'Secrétaire', 7566, to_date('09/11/81', 'DD/MM/YY'), 3000.00, NULL, 20);
INSERT INTO EMPLOYE VALUES (7876, 'Jaillot', 'Elodie', 'Secrétaire', 7788, to_date('23/09/81', 'DD/MM/YY'), 1100.00, NULL, 20);
INSERT INTO EMPLOYE VALUES (7782, 'Lapotre', 'Albert', 'Gérant', 7839, to_date('09/06/81', 'DD/MM/YY'), 2450.00, NULL, 10);
INSERT INTO EMPLOYE VALUES (7934, 'Chauvet', 'Sylvie', 'Secrétaire', 7782, to_date('23/01/82', 'DD/MM/YY'), 1300.00, NULL, 10);
INSERT INTO EMPLOYE VALUES (7698, 'Bourgeois', 'Joel', 'Gérant', 7839, to_date('01/05/81', 'DD/MM/YY'), 2450.00, NULL, 30);
INSERT INTO EMPLOYE VALUES (7900, 'Sibille', 'Lionel', 'Vendeur', 7698, to_date('03/12/81', 'DD/MM/YY'), 950.00, NULL, 30);
INSERT INTO EMPLOYE VALUES (7654, 'Martin', 'Bernard', 'Vendeur', 7698, to_date('28/09/81', 'DD/MM/YY'), 1250.00, 1400, 30);
INSERT INTO EMPLOYE VALUES (7499, 'Martin', 'Adam', 'Vendeur', 7698, to_date('20/02/81', 'DD/MM/YY'), 1600.00, 300, 30);
INSERT INTO EMPLOYE VALUES (7844, 'Turpin', 'Claire', 'Vendeur', 7698, to_date('08/09/81', 'DD/MM/YY'), 1500.00, 0.00, 30);

