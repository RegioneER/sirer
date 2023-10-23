/**
 * Copyright By Claudio Negri 01/05/2011 email: c.negri@cineca.it
 * 
 * Non distribuire senza rendere credito all'autore
 */

var maxRows = 20;

var colorNormal = "black";
var colorDisabled = "#777777";
var colorNormalFilter = "white";
var colorTempFilter = "pink";

var filterHelpText = "Filter";

var currentRow;
var filterMode;
var filterPage;
var filterPages;
var filterText;

function hideRows() {
	// domRowsNum=domTable.rows.length;
	// for(var i=0; i<domRowsNum; i++)
	// {
	// domTable.deleteRow(0);
	// }

	// faster
	// if(domTable.hasChildNodes())
	// {
	domTable.removeChild(domTable.tBodies[0]); // domTable.childNodes[2]
	domTable.appendChild(document.createElement("TBODY"));
	// }
}

function showRow(rowIndex) {
	var row = rows[rowIndex];
	var newRowIndex = domTable.tBodies[0].rows.length;
	var domRow = domTable.tBodies[0].insertRow(newRowIndex);
	for ( var i = 0; i < row.length; i++) {
		var domCell = domRow.insertCell(i);
		var domText = document.createTextNode(row[i]);
		domCell.appendChild(domText);
	}
}

function showNoResults() {
	var newRowIndex = domTable.tBodies[0].rows.length;
	var domRow = domTable.tBodies[0].insertRow(newRowIndex);
	var domCell = domRow.insertCell(0);
	domCell.colSpan = domTable.tHead.rows[0].cells.length;
	domCell.align = "center";
	var domText = document.createTextNode("-- no results --");
	domCell.appendChild(domText);
}

function updateControls() {
	var first = colorNormal;
	var prev = colorNormal;
	var next = colorNormal;
	var last = colorNormal;

	if (filterMode == false) {
		domClear.style.display = "none";

		if (currentRow < maxRows) {
			first = colorDisabled;
			prev = colorDisabled;
		}
		if (currentRow >= rows.length - maxRows) {
			next = colorDisabled;
			last = colorDisabled;
		}
	} else {
		domClear.style.display = "";

		if (filterPage == 0) {
			first = colorDisabled;
			prev = colorDisabled;
		}
		if (filterPage == filterPages - 1) {
			next = colorDisabled;
			last = colorDisabled;
		}
	}

	domFirst.style.color = first;
	domPrev.style.color = prev;
	domNext.style.color = next;
	domLast.style.color = last;
}

function showRows() {
	var first = currentRow;
	var last = currentRow + maxRows - 1;

	hideRows();

	if (first < 0) {
		first = 0;
	}
	if (last > rows.length - 1) {
		last = rows.length - 1;
	}
	for ( var i = first; i <= last; i++) {
		showRow(i);
	}
	if (last == -1) {
		showNoResults();
	}

	updateControls();
}

function checkConditions(row) {
	return (row[0].toUpperCase().indexOf(filterText) != -1 || row[1]
			.toUpperCase().indexOf(filterText) != -1)
}

function filterRows() {
	hideRows();

	var first = filterPage * maxRows;
	var last = (filterPage + 1) * maxRows - 1;

	var rowsFound = 0;
	for ( var i = 0; i < rows.length; i++) {
		if (checkConditions(rows[i])) {
			if (rowsFound >= first && rowsFound <= last) {
				showRow(i);
			}

			rowsFound++;
		}
	}
	if (rowsFound == 0) {
		showNoResults()
	}
	// console.log("filterPage: "+filterPage+" filterPages: "+filterPages);
	updateControls();
}

function startFilterRows() {
	filterText = domFilter.value.toUpperCase();

	if (filterText == "") {
		return;
	}

	domFilter.style.backgroundColor = colorNormalFilter;

	filterMode = true;
	filterPage = 0;

	var rowsFoundInCurrentPage = 0;
	var currentPage = 0;
	var i;
	for (i = 0; i < rows.length; i++) {
		if (checkConditions(rows[i])) {
			rowsFoundInCurrentPage++;
			if (rowsFoundInCurrentPage > maxRows) {
				currentPage++;
				rowsFoundInCurrentPage = 1;
			}
		}
	}
	filterPages = currentPage + 1;

	filterRows();
}

function filterKeyPress(event) {
	if (event.keyCode == 13) {
		startFilterRows();
	} else {
		domFilter.style.backgroundColor = colorTempFilter;
	}
}

function addText(input) {
	if (input.value == "") {
		input.value = filterHelpText;
	}
	if (input.value == filterHelpText) {
		input.style.color = colorDisabled;
	}
}

function removeText(input) {
	if (input.value == filterHelpText) {
		input.style.color = colorNormal;
		input.value = "";
	}
}

function clearFilter() {
	currentRow = 0;
	filterMode = false;

	domFilter.value = "";
	addText(domFilter);

	showRows();
}

function showFirstRows() {
	if (filterMode == false) {
		if (currentRow >= maxRows) {
			currentRow = 0;
			showRows();
		}
	} else {
		if (filterPage > 0) {
			filterPage = 0;
			filterRows();
		}
	}
}

function showPrevRows() {
	if (filterMode == false) {
		if (currentRow >= maxRows) {
			currentRow -= maxRows;
			showRows();
		}
	} else {
		if (filterPage > 0) {
			filterPage--;
			filterRows();
		}
	}
}

function showNextRows() {
	if (filterMode == false) {
		if (currentRow < rows.length - maxRows) {
			currentRow += maxRows;
			showRows();
		}
	} else {
		if (filterPage != filterPages - 1) {
			filterPage++;
			filterRows();
		}
	}
}

function showLastRows() {
	if (filterMode == false) {
		if (currentRow < rows.length - maxRows) {
			currentRow = Math.floor((rows.length - 1) / maxRows) * maxRows;
			showRows();
		}
	} else {
		if (filterPage != filterPages - 1) {
			filterPage = filterPages - 1;
			filterRows();
		}
	}
}

function initPagerTable(nometabella, row_showed) {
	var maxRows = row_showed;
	domTable = document.getElementById(nometabella);

	domFirst = document.getElementById("first");
	domPrev = document.getElementById("prev");
	domNext = document.getElementById("next");
	domLast = document.getElementById("last");
	domFilter = document.getElementById("filter");
	domClear = document.getElementById("clear");

	currentRow = 0;
	filterMode = false;
	showRows();

	domFilter.value = "";
	addText(domFilter);
}

//function addLoadEvent(func) {
//	var oldLoad = window.onload;
//
//	window.onload = function() {
//		if (oldLoad) {
//			oldLoad();
//		}
//
//		func();
//	}
//}
