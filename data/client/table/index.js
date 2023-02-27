const dynamicTable = new HtmlDynamicTable("#bells-table", ".row-template");
if (localStorage.getItem("table") != null) {
	getTable(localStorage.getItem("table"));
	localStorage.removeItem("table");
} else {
	dynamicTable.addRow();
}

addListener(".get-button", "click", (event) => {
	getTable(dynamicTable.table.tHead.querySelector('input[name="title"]').value);
})

function getTable(tableName)
{
	fetch(`/tables/${tableName}`, {
		method: "GET",
		headers: {
			"Content-Type": "application/json"
		}
	})
	.then(response => {
		if (response.ok) {
			return response.json();
		}
	})
	.then(data => {
		dynamicTable.table.tHead.querySelector('input[name="title"]').value = tableName;
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

function sendData(data, name) {
	return fetch('/tables', {
		method: 'POST',
		headers: { 'Content-Type': 'application/json' },
		body: data,
	})
}


function handleFormSubmit(event) {
	event.preventDefault();
	const data = serializeForm(event.target)
	const response = sendData(data);
}
