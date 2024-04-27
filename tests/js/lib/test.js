function describe(name, body) {
  console.log("suite: " + name);
  body();
}

function test(name, body) {
  console.log("  test: " + name);
  body();
}

function expect(value) {
  return {
    toBe: function (expected) {
      assert(value == expected);
    }
  };
}

