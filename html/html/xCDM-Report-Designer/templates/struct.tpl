{assign var=idx value="0" scope="root"}
{assign var=elpath value=""}
<form id="reportDesigner" name='reportDesigner' method='POST' action="index.php?/buildReport">
Inserisci il nome del prefisso delle viste da creare: <input type="text" name="rep_prefix" placeholder="prefisso"><br/>
<button type='submit' class='btn btn-info'>Costruisci report</button>
{include file="recursive-struct.tpl" startNode=$struct exploded=true elpath=$elpath}
<button type='submit' class='btn btn-info'>Costruisci report</button>
</form>