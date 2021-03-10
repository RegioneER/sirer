CREATE OR REPLACE TYPE listtable AS TABLE OF VARCHAR2 (255);


CREATE OR REPLACE FUNCTION explode (p_seperator IN VARCHAR2, p_string IN VARCHAR2)
   RETURN listtable AS
   l_string   LONG          DEFAULT p_string || p_seperator;
   l_data     listtable := listtable ();
   n          NUMBER;
BEGIN
   LOOP
      EXIT WHEN l_string IS NULL;
      n := INSTR (l_string, p_seperator);
      l_data.EXTEND;
      l_data (l_data.COUNT) := LTRIM (RTRIM (SUBSTR (l_string, 1, n - 1)));
      l_string := SUBSTR (l_string, n + 1);
   END LOOP;

   RETURN l_data;
END;

create or replace
function            is_number (string_in varchar2)
return boolean
is
val number;
begin
val := to_number (string_in);
return true;
exception
when others then return false;
end;

CREATE OR REPLACE FUNCTION explode_n (p_seperator IN VARCHAR2, p_string IN VARCHAR2)
   RETURN listtable AS
   l_string   LONG          DEFAULT p_string || p_seperator;
   l_data     listtable := listtable ();
   n          NUMBER;
BEGIN
--(SELECT * FROM TABLE (CAST (explode (',', v_list) AS listtable)))
--   FOR i IN (explode(p_seperator,p_string)) LOOP
   FOR i IN (SELECT * FROM TABLE (CAST (explode (p_seperator, p_string) AS listtable))) LOOP
      if is_number(i.COLUMN_VALUE) then
         l_data.EXTEND;
         l_data (l_data.COUNT) := i.COLUMN_VALUE;
      end if;
   END LOOP;

   RETURN l_data;
END;
