function check_passwords_forget() {

	var expr_username = /gargano/i;
	var expr_num = /[0-9]/;
	var expr_letter = /[a-zA-Z]/;
	var expr_char = /[\!"$%&()*+,-./:;<=>?\^]/;
	var new_pass_check = document.getElementById('new_password_check').value;
	var new_pass = document.getElementById('new_password').value;
//	var old_pass = document.getElementById('old_password').value;
	
	if(new_pass=="") { 
		alert("Inserire la nuova password"); 
		document.getElementById('new_password').style.border="1px solid red"; 
		return false;  
	}
	if(new_pass_check=="") { 
		alert("Inserire la nuova password di controllo");
		document.getElementById('new_password_check').style.border="1px solid red"; 
		return false; 
	}
	if(new_pass_check!=new_pass) { 
		alert("La nuova password e quella di controllo non coincidono"); 
		document.getElementById('new_password_check').style.border="1px solid red";
		document.getElementById('new_password').style.border="1px solid red";
		return false; 
	}
//	if(old_pass=="") { 
//		alert("Inserire la vecchia password"); 
//		document.getElementById('old_password').style.border="1px solid red"; 
//		return false; 
//	}
	if(new_pass.length<8) { 
		alert("La password deve essere di lunghezza minima di 8 caratteri");
		return false; 
	}
	
	if(expr_username.test(new_pass)) { alert("La password non puo'contenere l'username"); return false; }
	if(!expr_num.test(new_pass)) { alert("La password deve contenere almeno un numero"); return false; }
	if(!expr_letter.test(new_pass)) { alert("La password deve contenere almeno una lettera"); return false; }
	if(!expr_char.test(new_pass)) { alert("La password deve contenere almeno un carattere tra questi: !\"$%&()*+,-./:;<=>?\^"); return false; }
	
	return true;

}
function testPassword_forget(passwd) {
	var intScore = 0
	var strVerdict = "weak"
	var strLog = ""

	// PASSWORD LENGTH
	if (passwd.length < 5) // length 4 or less
	{
		intScore = (intScore + 3)
		strLog = strLog + "3 points for length (" + passwd.length + ")\n"
	} else if (passwd.length > 4 && passwd.length < 8) // length between 5 and
														// 7
	{
		intScore = (intScore + 6)
		strLog = strLog + "6 points for length (" + passwd.length + ")\n"
	} else if (passwd.length > 7 && passwd.length < 16)// length between 8 and
														// 15
	{
		intScore = (intScore + 15)
		strLog = strLog + "15 points for length (" + passwd.length + ")\n"
	} else if (passwd.length > 15) // length 16 or more
	{
		intScore = (intScore + 18)
		strLog = strLog + "18 point for length (" + passwd.length + ")\n"
	}

	// LETTERS (Not exactly implemented as dictacted above because of my limited
	// understanding of Regex)
	if (passwd.match(/[a-z]/)) // [verified] at least one lower case letter
	{
		intScore = (intScore + 1)
		strLog = strLog + "1 point for at least one lower case char\n"
	}

	if (passwd.match(/[A-Z]/)) // [verified] at least one upper case letter
	{
		intScore = (intScore + 5)
		strLog = strLog + "5 points for at least one upper case char\n"
	}

	// NUMBERS
	if (passwd.match(/\d+/)) // [verified] at least one number
	{
		intScore = (intScore + 5)
		strLog = strLog + "5 points for at least one number\n"
	}

	if (passwd.match(/(.*[0-9].*[0-9].*[0-9])/)) // [verified] at least three
													// numbers
	{
		intScore = (intScore + 5)
		strLog = strLog + "5 points for at least three numbers\n"
	}

	// SPECIAL CHAR
	if (passwd.match(/.[!,@,#,$,%,^,&,*,?,_,~]/)) // [verified] at least one
													// special character
	{
		intScore = (intScore + 5)
		strLog = strLog + "5 points for at least one special char\n"
	}

	// [verified] at least two special characters
	if (passwd.match(/(.*[!,@,#,$,%,^,&,*,?,_,~].*[!,@,#,$,%,^,&,*,?,_,~])/)) {
		intScore = (intScore + 5)
		strLog = strLog + "5 points for at least two special chars\n"
	}

	// COMBOS
	if (passwd.match(/([a-z].*[A-Z])|([A-Z].*[a-z])/)) // [verified] both upper
														// and lower case
	{
		intScore = (intScore + 2)
		strLog = strLog + "2 combo points for upper and lower letters\n"
	}

	if (passwd.match(/([a-zA-Z])/) && passwd.match(/([0-9])/)) // [verified]
																// both letters
																// and numbers
	{
		intScore = (intScore + 4)
		strLog = strLog + "4 combo points for letters and numbers\n"
	}

	// [verified] letters, numbers, and special characters
	if (passwd
			.match(/([a-zA-Z0-9].*[!,@,#,$,%,^,&,*,?,_,~])|([!,@,#,$,%,^,&,*,?,_,~].*[a-zA-Z0-9])/)) {
		intScore = (intScore + 4)
		strLog = strLog
				+ "4 combo points for letters, numbers and special chars\n"
	}

	if (intScore < 16) {
		strVerdict = "invalid";
		document.getElementById("colorMe").style.background = "red";
	} else if (intScore > 15 && intScore < 20) {
		strVerdict = "weak";
		document.getElementById("colorMe").style.background = "orange";
	} else if (intScore > 19 && intScore < 30) {
		strVerdict = "normal";
		document.getElementById("colorMe").style.background = "yellow";
	} else if (intScore > 29 && intScore < 40) {
		strVerdict = "strong";
		document.getElementById("colorMe").style.background = "green";
	} else {
		strVerdict = "stronger";
		document.getElementById("colorMe").style.background = "limeGreen";
	}
// document.getElementById("score").value=intScore;
// document.getElementById("verdict").value=strVerdict;
	// document.getElementById("matchlog").value=strLog;
	document.getElementById("colorMe").innerHTML = "    " + strVerdict;
	var perc=intScore*3;
	if(perc > 100) perc=100;
	document.getElementById("colorMe").style.width = perc+"%";
//alert(intScore);
	return intScore + " " + strVerdict;

}