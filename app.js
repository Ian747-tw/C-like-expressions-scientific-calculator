const exprEl = document.getElementById("expr");
const resultEl = document.getElementById("resultValue");
const evalBtn = document.getElementById("evalBtn");
const clearBtn = document.getElementById("clearBtn");

function powLogProcess(s){
  for(let i = 0; i < s.length; i++){
    if((s[i] === 'l' && s[i + 1] === 'o') || (s[i] === 'p' && s[i + 1] === 'o')){
      let tempi = i + 4;
      let ct = 1;
      const substr0 = s.slice(0, i);
      let substr1 = "";
      while(!(ct === 1 && s[tempi] === ',')){
        substr1 += s[tempi];
        if(s[tempi] === '(') ct++;
        if(s[tempi] === ')') ct--;
        tempi++;
      }
      tempi++;
      ct = 0;
      let substr2 = "";
      while(!(ct === 0 && s[tempi] === ')')){
        substr2 += s[tempi];
        if(s[tempi] === '(') ct++;
        if(s[tempi] === ')') ct--;
        tempi++;
      }
      const substr3 = s.slice(tempi + 1);
      s = substr0 + '(' + '(' + substr1 + ')' + '(' + substr2 + ')' + ')' + s[i] + substr3;
    }
  }
  return s;
}

function funcProcess(s){
  for(let i = 0; i < s.length; i++){
    if(s[i] === 'e' && s[i + 1] === 'x'){
      s = moveSingleArgFunc(s, i, 3, s[i]);
    }else if(s[i] === 's' && s[i + 1] === 'i'){
      s = moveSingleArgFunc(s, i, 3, s[i]);
    }else if(s[i] === 'c' && s[i + 1] === 'o'){
      s = moveSingleArgFunc(s, i, 3, s[i]);
    }else if(s[i] === 's' && s[i + 1] === 'q'){
      s = moveSingleArgFunc(s, i, 4, s[i + 1]);
    }else if(s[i] === 'f' && s[i + 1] === 'a'){
      s = moveSingleArgFunc(s, i, 4, s[i]);
    }
  }
  return s;
}

function moveSingleArgFunc(s, i, offset, funcChar){
  const substr0 = s.slice(0, i);
  let tempi = i + offset;
  let substr1 = "";
  let ct = 0;
  while(!(ct === 1 && s[tempi] === ')')){
    substr1 += s[tempi];
    if(s[tempi] === '(') ct++;
    if(s[tempi] === ')') ct--;
    tempi++;
  }
  substr1 += ')';
  const substr2 = s.slice(tempi + 1);
  return substr0 + substr1 + funcChar + substr2;
}

function unaryProcess(s){
  for(let i = s.length - 1; i >= 0; i--){
    const isUnary = (i === 0 && "+-!~".includes(s[i])) ||
      (i > 0 && "+-!~".includes(s[i]) && !(/[0-9a-zA-Z)]/.test(s[i - 1])));
    if(!isUnary) continue;
    if(s[i + 1] === '('){
      let ct = 1;
      let tempi = i + 2;
      const substr0 = s.slice(0, i);
      let substr1 = "";
      while(!(ct === 1 && s[tempi] === ')')){
        if(s[tempi] === '(') ct++;
        if(s[tempi] === ')') ct--;
        substr1 += s[tempi];
        tempi++;
      }
      let substr2 = "";
      let substr3 = s.slice(tempi + 1);
      if(/[a-zA-Z]/.test(s[tempi + 1]) && s[tempi + 1] !== 'z'){
        substr2 += s[tempi + 1];
        substr3 = s.slice(tempi + 2);
      }
      if(s[tempi + 1] === 'u'){
        substr2 += s[tempi + 2];
        substr3 = s.slice(tempi + 3);
      }
      s = substr0 + '(' + '(' + substr1 + ')' + substr2 + ')' + 'u' + s[i] + substr3;
    }else if(/[0-9.]/.test(s[i + 1])){
      const substr0 = s.slice(0, i);
      let substr1 = "";
      let tempi = i + 1;
      while(/[0-9.]/.test(s[tempi])){
        substr1 += s[tempi];
        tempi++;
      }
      const substr2 = s.slice(tempi);
      s = substr0 + '(' + substr1 + ')' + 'u' + s[i] + substr2;
    }else{
      throw new Error("Unary parse error");
    }
  }
  return s;
}

function tokenize(line){
  const s = [];
  let tmp = "";
  for(let i = 0; i < line.length; i++){
    const ch = line[i];
    if(/[0-9.]/.test(ch)){
      tmp += ch;
    }else if(i && /[0-9.]/.test(line[i - 1])){
      s.push(tmp);
      tmp = "";
    }

    if(ch === '>' || ch === '<' || ch === '=' || ch === '&' || ch === '|'){
      if(i + 1 < line.length && line[i + 1] === ch){
        if(tmp === ""){
          tmp += ch + line[i + 1];
          i++;
        }else{
          throw new Error("Token error");
        }
      }else{
        if(tmp === "") tmp += ch;
        else throw new Error("Token error");
      }
      s.push(tmp);
      tmp = "";
    }else if(ch === '!'){
      if(i + 1 < line.length && line[i + 1] === '='){
        if(tmp === ""){
          tmp += ch + line[i + 1];
          i++;
        }else{
          throw new Error("Token error");
        }
      }else{
        throw new Error("Token error");
      }
      s.push(tmp);
      tmp = "";
    }else if(ch === 'u'){
      if(i + 1 < line.length){
        if(tmp === ""){
          tmp += ch + line[i + 1];
          i++;
        }else{
          throw new Error("Token error");
        }
      }else{
        throw new Error("Token error");
      }
      s.push(tmp);
      tmp = "";
    }else if(!/[0-9.]/.test(ch) && ch !== 'z'){
      if(tmp === "") tmp += ch;
      else throw new Error("Token error");
      s.push(tmp);
      tmp = "";
    }
  }
  return s;
}

function toPostfix(tokens){
  const priority = {
    "||": 1,
    "&&": 2,
    "|": 3,
    "^": 4,
    "&": 5,
    "==": 6,
    "!=": 6,
    "<<": 7,
    ">>": 7,
    "+": 8,
    "-": 8,
    "*": 9,
    "/": 9,
    "%": 9
  };
  const opStack = [];
  const out = [];
  for(let i = 0; i < tokens.length; i++){
    const t = tokens[i];
    if(/[0-9.]/.test(t[0])){
      out.push(t);
    }else if(t === "("){
      opStack.push(t);
    }else if(t === ")"){
      while(opStack.length && opStack[opStack.length - 1] !== "("){
        out.push(opStack.pop());
      }
      if(opStack.length && opStack[opStack.length - 1] === "(") opStack.pop();
      if(i + 1 < tokens.length && /[a-zA-Z]/.test(tokens[i + 1][0])){
        i++;
        out.push(tokens[i]);
      }
    }else if(priority[t]){
      while(opStack.length && opStack[opStack.length - 1] !== "(" &&
        priority[opStack[opStack.length - 1]] >= priority[t]){
        out.push(opStack.pop());
      }
      opStack.push(t);
    }
  }
  while(opStack.length) out.push(opStack.pop());
  return out;
}

function evalPostfix(tokens){
  const stack = [];
  const toLL = v => (v | 0);
  for(const t of tokens){
    if(/[0-9.]/.test(t[0])){
      stack.push(parseFloat(t));
      continue;
    }
    if(t === "u+" || t === "u-" || t === "u!" || t === "u~"){
      if(!stack.length) throw new Error("Eval error");
      const a = stack.pop();
      if(t === "u+") stack.push(+a);
      else if(t === "u-") stack.push(-a);
      else if(t === "u!") stack.push(a === 0 ? 1 : 0);
      else stack.push(~toLL(a));
      continue;
    }
    if(t === "s" || t === "c" || t === "e" || t === "q" || t === "f"){
      if(!stack.length) throw new Error("Eval error");
      const a = stack.pop();
      if(t === "s") stack.push(Math.sin(a));
      else if(t === "c") stack.push(Math.cos(a));
      else if(t === "e") stack.push(Math.exp(a));
      else if(t === "q") stack.push(Math.sqrt(a));
      else stack.push(Math.abs(a));
      continue;
    }
    if(t === "l" || t === "p"){
      if(stack.length < 2) throw new Error("Eval error");
      const b = stack.pop();
      const a = stack.pop();
      if(t === "l") stack.push(Math.log10(b) / Math.log10(a));
      else stack.push(Math.pow(a, b));
      continue;
    }
    if(stack.length < 2) throw new Error("Eval error");
    const b = stack.pop();
    const a = stack.pop();
    if(t === "+") stack.push(a + b);
    else if(t === "-") stack.push(a - b);
    else if(t === "*") stack.push(a * b);
    else if(t === "/") stack.push(a / b);
    else if(t === "%") stack.push(toLL(a) % toLL(b));
    else if(t === "<<") stack.push(toLL(a) << toLL(b));
    else if(t === ">>") stack.push(toLL(a) >> toLL(b));
    else if(t === "==") stack.push(a === b ? 1 : 0);
    else if(t === "!=") stack.push(a !== b ? 1 : 0);
    else if(t === "&") stack.push(toLL(a) & toLL(b));
    else if(t === "^") stack.push(toLL(a) ^ toLL(b));
    else if(t === "|") stack.push(toLL(a) | toLL(b));
    else if(t === "&&") stack.push((a !== 0 && b !== 0) ? 1 : 0);
    else if(t === "||") stack.push((a !== 0 || b !== 0) ? 1 : 0);
    else throw new Error("Eval error");
  }
  if(stack.length !== 1) throw new Error("Eval error");
  return stack[0];
}

function evaluate(expr){
  let line = expr.replace(/\s+/g, "") + "z";
  line = powLogProcess(line);
  line = funcProcess(line);
  line = unaryProcess(line);
  const tokens = tokenize(line);
  const postfix = toPostfix(tokens);
  return evalPostfix(postfix);
}

function renderResult(value){
  if(Number.isNaN(value)) resultEl.textContent = "NaN";
  else if(!Number.isFinite(value)) resultEl.textContent = value > 0 ? "∞" : "-∞";
  else resultEl.textContent = String(value);
}

evalBtn.addEventListener("click", () => {
  try{
    const v = evaluate(exprEl.value);
    renderResult(v);
  }catch(err){
    resultEl.textContent = err.message || "Error";
  }
});

clearBtn.addEventListener("click", () => {
  exprEl.value = "";
  resultEl.textContent = "—";
});
