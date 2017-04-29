select a from (select a,b from (select sum(c) from (select sum(d) from a) a1 join j) a2) a3;
quit;
