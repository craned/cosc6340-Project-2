drop table D;
create table D (A int, PRIMARY KEY(A));
insert into D values(1);
insert into D values(2);
insert into D values(8);
select sum(a) from D group by a;
quit;
