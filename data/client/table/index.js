const dynamicTable = new HtmlDynamicTable("#bells-table", ".row-template");
dynamicTable.addRow();
addListener(".get-button", "click", handleGetButton)

function handleGetButton(event)
{
	let request = new XMLHttpRequest();
	request.open('GET', "/bells.json");
	request.responseType = 'json';
	request.send();

	request.onload = function()
	{
		let data = request.response;
		loadJson(data, dynamicTable);
	}
}
