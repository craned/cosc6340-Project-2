select c from C2 join j WHERE c=1;
SELECT a from (select b from (select c from (select d from t) C2 join j WHERE c=1) c3) c4;
SELECT a from (select b from (select c from (select d from t) C2) c3) c4;
select c from (select d from t) C2;
