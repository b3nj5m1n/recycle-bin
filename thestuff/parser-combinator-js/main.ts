interface EdnChar {
    kind: "ednChar",
    value: String,
}
type ednValue = EdnChar

function inputRead(input) {
    return input.rest[0];
}

function inputAdvance(input, n) {
    return input.rest.substring(n);
}

// Based on https://www.theorangeduck.com/page/you-could-have-invented-parser-combinators
function lit(c) {
    return (function (input) {
        let r = inputRead(input);
        if (r == c) {
            return { error: false, result: [c], rest: inputAdvance(input, 1) };
        } else {
            return { error: true, info: `Expected ${c}, got ${r}` };
        }
    });
}

function or(parser0, parser1) {
    return (function (input) {
        let result0 = parser0(input);
        if (!result0.error) { return result0; }
        let result1 = parser1(input);
        if (!result1.error) { return result1; }
        return { error: true, info: `Idk` };
    });
}

function and(parser0, parser1) {
    return (function (input) {
        let result0 = parser0(input);
        if (result0.error) { return result0; }
        let result1 = parser1(result0);
        if (result1.error) { return result1; }
        return { error: false, result: result0.result.concat(result1.result), rest: result1.rest };
    });
}

function chain(...parsers) {
    return (function (input) {
        let last_result = parsers[0](input);
        if (last_result.error) { return last_result; }
        for (let i = 1; i < parsers.length; i++) {
            let result = parsers[i](last_result);
            if (result.error) { return result; }
            last_result = { error: false, result: last_result.result.concat(result.result), rest: result.rest };
        }
        return last_result;
    });
}

function repeat(parser, n) {
    return (function (input) {
        let last_result = parser(input);
        if (last_result.error) { return last_result; }
        for (let i = 1; i < n; i++) {
            let result = parser(last_result);
            if (result.error) { return result; }
            last_result = { error: false, result: last_result.result.concat(result.result), rest: result.rest };
        }
        return last_result;
    });
}

function zero_or_one(parser) {
    return (function (input) {
        let last_result = parser(input);
        if (last_result.error) { return input; }
        return last_result;
    });
}

function parseChar() {
    return (function (input) {
        let r = inputRead(input);
        if (r.match(/[a-z]/i)) {
            return { error: false, result: [r], rest: inputAdvance(input, 1) };
        } else {
            return { error: true, info: `Expected char, got '${r}'` };
        }
    });
}

function parseNumberRadix(radix) {
    return (function (input) {
        let r = inputRead(input);
        let converted = parseInt(r, radix);
        if (!isNaN(converted)) {
            return { error: false, result: [converted], rest: inputAdvance(input, 1) };
        } else {
            return { error: true, info: `Expected number in base ${radix}, got '${r}'` };
        }
    });
}

function parseNumber() {
    return parseNumberRadix(10);
}

function parseNumberHex() {
    return parseNumberRadix(16);
}

function parseHexColor() {
    return chain(zero_or_one(lit('#')), repeat(parseNumberHex(), 6));
}

var input = { error: false, result: [], rest: "#ff0066" };
/* let parser = or(
    and(lit('a'), lit('b')),
    and(lit('c'), lit('d'))); */
// let parser = chain(parseChar(), parseNumberHex(), parseNumberHex());
let parser = parseHexColor();
let result = parser(input);
console.log(result);

