const dynamicTable = new HtmlDynamicTable("#bells-table", ".row-template");
if (localStorage.getItem("table") != null) {
	getTable(localStorage.getItem("table"));
	localStorage.removeItem("table");
} else {
	dynamicTable.addRow();
}

addListener(".get-button", "click", (event) => {
	getTable(dynamicTable.table.tHead.querySelector("input[name=title]").value);
})

function getTable(tableName)
{
	getData(`/tables/${tableName}`).then(data => {
		dynamicTable.table.tHead.querySelector("input[name=title]").value = tableName;
		loadArray(data, dynamicTable);
	});
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

function handleFormSubmit(event) {
	event.preventDefault();
	const data = serializeForm(event.target)
	const response = sendData("/tables", data);
}
