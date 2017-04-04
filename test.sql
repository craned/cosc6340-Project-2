create table t (c1 int, c2 char(6), primary key (c2));
insert into t values (1, 'test');
show table t;
show tables;
select a,b,c,d from deep join j;
select a from (select a,b from (select a,b,c,d from deep join (select a,b,c from jn) tt on t.a = t1.b) t1) t3s;
quit;
