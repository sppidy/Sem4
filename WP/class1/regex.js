function matchStringInsensitive(input, pattern) {
    const regex = new RegExp(pattern, 'i');
    return regex.test(input);
}

function matchStringSensitive(input, pattern) {
    const regex = new RegExp(pattern);
    return regex.test(input);
}

const inputString = "Hello World";
const pattern = "hello";

console.log(matchStringInsensitive(inputString, pattern));
console.log(matchStringSensitive(inputString, pattern));

document.body.style.backgroundColor = 'lightgrey';
function searchAndReplace(input, searchPattern, replacement, caseSensitive = false) {
    const flags = caseSensitive ? 'g' : 'gi';
    const regex = new RegExp(searchPattern, flags);
    return input.replace(regex, replacement);
}

const searchContainer = document.createElement('div');
searchContainer.style.margin = '20px';
searchContainer.style.textAlign = 'center';

const searchInput = document.createElement('input');
searchInput.type = 'text';
searchInput.placeholder = 'Search term';
searchInput.style.margin = '5px';
searchInput.style.padding = '5px';

const replaceInput = document.createElement('input');
replaceInput.type = 'text';
replaceInput.placeholder = 'Replace with';
replaceInput.style.margin = '5px';
replaceInput.style.padding = '5px';

const caseCheckbox = document.createElement('input');
caseCheckbox.type = 'checkbox';
caseCheckbox.id = 'caseSensitive';
const caseLabel = document.createElement('label');
caseLabel.htmlFor = 'caseSensitive';
caseLabel.textContent = 'Case sensitive';
caseLabel.style.margin = '0 10px 0 5px';

const replaceButton = document.createElement('button');
replaceButton.textContent = 'Replace';
replaceButton.style.margin = '5px';
replaceButton.style.padding = '5px 10px';

replaceButton.addEventListener('click', () => {
    try {
        const searchTerm = searchInput.value;
        const replaceTerm = replaceInput.value;
        const caseSensitive = caseCheckbox.checked;
        
        const paragraph = document.querySelector('p');
        if (paragraph && searchTerm) {
            paragraph.innerHTML = searchAndReplace(paragraph.innerHTML, searchTerm, replaceTerm, caseSensitive);
        }
    }
    catch (error) {
        console.error(error);
    }
});

searchContainer.appendChild(searchInput);
searchContainer.appendChild(replaceInput);
searchContainer.appendChild(caseCheckbox);
searchContainer.appendChild(caseLabel);
searchContainer.appendChild(replaceButton);

document.body.append(searchContainer);

const rdiv = document.createElement('div'); 
rdiv.id = 'rdiv';
let a = document.createElement('h1');
document.body.appendChild(a);
a.innerHTML = 'Hello World';
a.style.color = 'red';
a.style.fontFamily = 'Arial';
a.style.textAlign = 'center';
const randomWords = ["apple", "banana", "cherry", "date", "elderberry", "fig", "grape", "honeydew", "kiwi", "lemon", "mango", "nectarine", "orange", "papaya", "quince", "raspberry", "strawberry", "tangerine", "ugli", "vanilla", "watermelon", "xigua", "yellowfruit", "zucchini", "apricot", "blackberry", "blueberry", "cantaloupe", "dragonfruit", "elderflower", "feijoa", "gooseberry", "huckleberry", "jackfruit", "kumquat", "lime", "mulberry", "olive", "peach", "plum", "pomegranate", "rambutan", "starfruit", "tamarind", "ugni", "voavanga", "wolfberry", "ximenia", "yumberry", "ziziphus", "avocado", "bilberry", "clementine", "damson", "eggplant", "fingerlime", "grapefruit", "hackberry", "imbe", "jabuticaba", "kiwano", "longan", "mandarin", "nashi", "olive", "persimmon", "quandong", "rowan", "soursop", "tangelo", "umbu", "voavanga", "waxapple", "ximenia", "yuzu", "zinfandel", "acerola", "breadfruit", "cupuacu", "durian", "elderberry", "fig", "grapefruit", "honeyberry", "indianfig", "jostaberry", "kiwi", "lemon", "mangosteen", "nectarine", "orange", "pineapple", "quince", "rhubarb", "salak", "tamarillo", "ugli", "voavanga", "watermelon", "ximenia", "yellowpassionfruit", "zucchini"];
let randomParagraph = "";
for (let i = 0; i < 100; i++) {
    const randomIndex = Math.floor(Math.random() * randomWords.length);
    randomParagraph += randomWords[randomIndex] + " ";
}

let p = document.createElement('p');
document.body.appendChild(p);
p.innerHTML = `${randomParagraph.trim()}`;
p.style.color = 'blue';
p.style.fontFamily = 'Verdana';
p.style.textAlign = 'justify';

rdiv.appendChild(a);
rdiv.appendChild(p);
document.body.appendChild(rdiv);
