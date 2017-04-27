SELECT * FROM T where C='A' group BY 'test' ORDER BY 'test1';
SELECT * FROM T where C='A';
SELECT * FROM T where C='A' ORDER BY 'test1';
SELECT * FROM T where C='A' group BY 'test';
SELECT * FROM T group BY 'test';
SELECT * FROM T order BY 'test';
SELECT * FROM T join u on a=6 group BY 'test';
SELECT * FROM T join u on a=6 order BY 'test';
select x.k,y.c,x.c
from (select * from t where c='a') x
join (select k, c from z) y on y.k=x.k;
Quit;
