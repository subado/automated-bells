import HtmlDynamicTable from "./HtmlDynamicTable.js";
import { addListeners } from "/utils.js";
import * as Data from "/data.js";

const dynamicTable = new HtmlDynamicTable("#bells-table", ".row-template");
if (localStorage.getItem("table") != null) {
	getTable(localStorage.getItem("table"));
	localStorage.removeItem("table");
} else {
	dynamicTable.addRow();
}

addListeners(".get-button", "click", (event) => {
	getTable(dynamicTable.table.tHead.querySelector("input[name=title]").value);
})

async function getTable(tableName)
{
	const table = await Data.get(`/tables/${tableName}`);
	dynamicTable.table.tHead.querySelector("input[name=title]").value = tableName;
	loadArray(table, dynamicTable);
}

const form = document.querySelector("#bells-form");
form.addEventListener("submit", handleFormSubmit);

function serializeForm(formNode) {
	const formData = new FormData(formNode);
	const formArray = Array.from(formData.entries());
	const pairs = formArray.reduce((result, obj) => {
		result.push({ [obj[0]]: obj[1] });
		return result;
	}, []);
	return JSON.stringify(pairs);
}

async function handleFormSubmit(event) {
	event.preventDefault();
	const data = serializeForm(event.target)
	const { ok } = await Data.send("/tables", data);

	if (ok) {
		alert("The schedule was saved successfully");
	} else {
		alert("Something went wrong");
	}
}

function loadArray(array, dynamicTable)
{
	deleteChildren(dynamicTable.table.tBodies[0]);

	for (let i = 0; i < array.length; i++)
	{
		dynamicTable.addRow();
		dynamicTable.table.tBodies[0].rows[i].querySelector('input[name="time"]').value = array[i];
	}
}

function deleteChildren(element)
{
	let first = element.firstElementChild;

	while (first)
	{
		first.remove();
		first = element.firstElementChild;
	}
}
