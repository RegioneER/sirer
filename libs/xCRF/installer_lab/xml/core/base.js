function kill_all_children(node)
{
    // In the spirit of Pontius Pilatus
    var i;
    for(i=0;i<node.childNodes.length;i++)
    {        
        var n=node.childNodes[i];
        if(n.nodeName!='OPTION')
        {
            if(n.type=="checkbox"||n.type=="radio")
            {
                if(!!n.checked)n.checked=false;                
            }else{
                if(!!n.value)n.value='';
            }    
            if(!!n.checkstate)n.checkstate();
        }
        kill_all_children(n);
    }
}

function join_array()
{
    var r=[];
    var i;
    var j;
    for(i=0;i<arguments.length;i++)
    {
        var a=arguments[i];
        for(j=0;j<a.length;j++)
        {
            r.push(a[j])
        }       
    }
    return r;
}

function array_contains(arr,val)
{
    var i;
    for(i=0;i<arr.length;i++)
    {
        if(arr[i]==val)return true;
    }    
    return false;
}

function toInt(x)
{
    if(x=='')return NaN;
    return x.replace(',','.')-0;
}

function removeKomma(x)
{ 
    var el=document.forms[0].elements;
    el[x].value = el[x].value.replace(',','.');
    
}

function roundup(val,len,fix)
{
    var r=val.toFixed(fix);
    for(var i=len;r.length>len && i>0;i--)r=val.toPrecision(i);
    return r;
}

//Invokes another Function OnReturn from an Function
function onReturnFunction(orginal,func)
{    
    return function()
    {
        var r=null;
        if(orginal)r=orginal.apply({},arguments);
        func();
        if(orginal)return r;
    }    
}

function func_on_node_action(node,func)
{    
    node.onkeyup=onReturnFunction(node.onkeyup,func);
    node.onchange=onReturnFunction(node.onchange,func);
    node.checkstate=onReturnFunction(node.checkstate,func);
    node.onclick=onReturnFunction(node.onclick,func);
}

function func_on_nodes_action(nodes,func)
{   
    var i;
    for(i=0;i<nodes.length;i++)func_on_node_action(nodes[i],func);
} 

function get_radio_clear_button(radio)
{
    var x=radio[radio.length-1].parentNode.parentNode.childNodes;
    return x[x.length-1].childNodes[0];    
}

function deriveValue(monitor,func,target)
{
    var i;
    function f()
    {   
        var i;
        func();
        for(i=0;i<target.length;i++)
        {
            if(!!target[i].checkstate)target[i].checkstate();
        }
    }
    func_on_nodes_action(monitor,f);    
    for(i=0;i<target.length;i++)
    {
	target[i].disabled=true;
    }    
}

function func_hide_row(monitor,func,rows)
{
    var i;
    if(typeof rows=='string')rows=[rows];
    function f()
    {
        var i;
        if(func())
        {
            for(i=0;i<rows.length;i++)document.getElementById('cell_'+rows[i]).parentNode.style.display='';
        }else{
            for(i=0;i<rows.length;i++)
            {
                var tr=document.getElementById('cell_'+rows[i]).parentNode;
                if(tr.style.display!='none')
                {
                    tr.style.display='none';
                    kill_all_children(tr);
                }
            }
        }
    }  
    func_on_nodes_action(monitor,f);
    if(func())
    {
        for(i=0;i<rows.length;i++)document.getElementById('cell_'+rows[i]).parentNode.style.display='';
    }else{
        for(i=0;i<rows.length;i++)document.getElementById('cell_'+rows[i]).parentNode.style.display='none';
    }
}

function radio_hide_row(radio,nrs,rows)
{
    var rads=document.forms[0].elements[radio]
    function t()
    {
        var i;
        for(i=0;i<nrs.length;i++)
        {
            if(rads[nrs[i]].checked)return true;
        }
        return false;
    }    
    func_hide_row(join_array(rads,[get_radio_clear_button(rads)]),t,rows);
}

function tickbox_hide_row(tickbox,state,rows)
{
    var tick=document.forms[0].elements[tickbox];
    function t()
    {
        return tick.checked==state;
    }    
    func_hide_row([tick],t,rows);
}

function textbox_hide_row(textbox,rows)
{
    var text=document.forms[0].elements[textbox];
    function t()
    {
        if(toInt(text.value) !='') return true;
		return false;
    }    
    func_hide_row([text],t,rows);
}

function select_hide_row(select,values,rows)
{
    var sel=document.forms[0].elements[select];
    function t()
    {        
        return array_contains(values,sel.value);
    }    
    func_hide_row([sel],t,rows);
}

function elDate(variable,latemiss)
{
    var el=document.forms[0].elements;
    var year=el[variable+'Y'].value;
    var month=el[variable+'M'].value;
    var day=el[variable+'D'].value;    
    if(isNaN(year))return new Date(0,0,0);
    if(isNaN(month) || month=='' || month=='-9911' || month=='-9922')month=!latemiss ? 1 : 12;
    if(isNaN(day))
    if(!latemiss)
    {
        day=0;
    }else{
        day=-1;
        month=month+1;
    }    
    return new Date(year,month-1,day);
}

function hdDate(variable)
{
    var x=Date.parseExact(document.forms[0].elements[variable].value.replace('00:00:00','').replace(/^[ ]+|[ ]+$/g,''),['ddMMyyyy','d-M-yyyy','d.M.yyyy','d/M/yyyy']);
    if(x==null)return new Date(0,0,0);
    return x;
}

function elTime(variable,date)
{   
    var el=document.forms[0].elements;
    var hours=el[variable+'_H'].value;
    var minutes=el[variable+'_M'].value;
    if(date==undefined)
    {
        date=new Date(0,0,0);
    }else{
        date=new Date(date);
    }  
    if(isNaN(hours))hours=0;
    if(isNaN(minutes))minutes=0;
    date.addHours(hours).addMinutes(minutes);
    if(isNaN(date))
    {
        date=new Date(0,0,0);
    }
    return date;
}

function hdTime(variable,date)
{
    var el=document.forms[0].elements;
    var hours=el[variable].value.substring(0,2);
    var minutes=el[variable].value.substring(2,4);
    if(date==undefined)
    {
        date=new Date(0,0,0);
    }else{
        date=new Date(date);
    }  
    if(isNaN(hours))hours=0;
    if(isNaN(minutes))minutes=1;
    date.addHours(hours).addMinutes(minutes);
    if(isNaN(date))
    {
        date=new Date(0,0,0);
    }
    return date;
}

function lastTimePoint()
{
    var i=0;
    var r=null;
    for(;i<arguments.length;i++)
    {
        if(!arguments[i].equals(MissingDate()))
        {
            r=arguments[i];
            break;            
        }     
    }
    if(r==null)return MissingDate();
    for(;i<arguments.length;i++)
    {
        if(arguments[i].isAfter(r))
        {
            r=arguments[i];
        }     
    }    
    return r;   
}

function MissingDate()
{
    return new Date(0,0,0);
}

function anyChecked(a)
{
    for(var i=0;i<a.length;i++)
    {
        if(a[i].checked)return true;
    }
    return false;
}

$(window).load(function (){
    var form=document.forms[0];
    var el=form.elements;
    var annulla=el['annulla'];
    if(!annulla)return;
    annulla.type='button';
    annulla.onclick=function (){
        form.reset();
        for(var i=0;i<el.length;i++)
        {
            var n=el[i];
            if(!!n.checkstate)n.checkstate();
        }
    };
});