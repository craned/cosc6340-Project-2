CREATE TABLE T (K INT, A INT, C CHAR(1), PRIMARY KEY(A));
CREATE TABLE S (I INT, B INT, D CHAR(3), PRIMARY KEY(I));
CREATE TABLE Z (K INT, C CHAR(1), PRIMARY KEY(K));
INSERT INTO T VALUES(1,1,'A');
INSERT INTO T VALUES(2,1,'A');
INSERT INTO T VALUES(3,2,'A');
INSERT INTO T VALUES(4,3,'A');
INSERT INTO T VALUES(9,4,'A');
INSERT INTO T VALUES(6,1,'B');
INSERT INTO T VALUES(7,1,'C');
INSERT INTO T VALUES(8,5,'a');
INSERT INTO T VALUES(9,6,'a');
INSERT INTO S VALUES(2,1,'ABA');
INSERT INTO S VALUES(3,1,'ACA');
INSERT INTO S VALUES(4,1,'ADA');
INSERT INTO S VALUES(5,1,'ACM');
INSERT INTO S VALUES(6,1,'mba');
INSERT INTO S VALUES(7,1,'ABC');
INSERT INTO S VALUES(8,3,'ABA');
INSERT INTO S VALUES(9,2,'AAA');
INSERT INTO S VALUES(0,3,'BBB');
--INSERT INTO Z VALUES(1,'D');
INSERT INTO Z VALUES(2,'D'); 
INSERT INTO Z VALUES(3,'D');
--INSERT INTO Z VALUES(10,'c');  /* PK VIOLATION   */
INSERT INTO Z
SELECT K,C
FROM T
WHERE C=‘A’;
SELECT *
FROM Z;
Quit;