describe("object", function() {
  test("empty declaration", function() {
    var obj = {};
    expect(Object.length(obj)).toBe(0);
  });

  test("single property declaration", function() {
    var obj = {
      a: 1
    };
    expect(Object.length(obj)).toBe(1);
    expect(obj.a).toBe(1);
    expect(obj["a"]).toBe(1);
  });

  test("nested property declaration", function() {
    var a = {
      b: {
        c: {
          d: 1
        }
      }
    };
    expect(a.b.c.d).toBe(1);
    expect(a["b"]["c"]["d"]).toBe(1);
    expect(a["b"].c["d"]).toBe(1);
  });
});
