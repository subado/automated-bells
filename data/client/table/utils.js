function getRowOfButton(button)
{
	return getParentElement(button, "tr");
}

function getParentElement(element, parent)
{
	while (element.localName != parent)
	{
		element = element.parentElement;
	}

	return element;
}

function loadJson(jsonData, dynamicTable)
{
	deleteChildren(dynamicTable.table.tBodies);

	for (let i = 0; i < data.length; i++)
	{
		dynamicTable.addRow();
		dynamicTable.table.rows[i].querySelectorAll('input[name="time"]').value = data[i];
	}
}

function addListener(selector, eventType, handler, obj = document)
{
	const elements = obj.querySelectorAll(selector);

	Array.from(elements).forEach((element) =>
	{
		element.addEventListener(eventType, handler);
	});
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
