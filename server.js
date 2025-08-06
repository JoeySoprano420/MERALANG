const {
    createConnection,
    TextDocuments,
    ProposedFeatures,
    CompletionItemKind,
} = require('vscode-languageserver/node');

const connection = createConnection(ProposedFeatures.all);
const documents = new TextDocuments();

connection.onInitialize(() => {
    return {
        capabilities: {
            textDocumentSync: documents.syncKind,
            completionProvider: { resolveProvider: false }
        }
    };
});

// Simple completion provider with MeraLang keywords
const keywords = [
    'capsule', 'func', 'var', 'const', 'import', 'return', 'if', 'else', 'while', 'for',
    'break', 'continue', 'macro', 'endmacro', 'when', 'true', 'false'
];

connection.onCompletion((_textDocumentPosition) => {
    return keywords.map(k => ({
        label: k,
        kind: CompletionItemKind.Keyword,
        data: k
    }));
});

documents.listen(connection);
connection.listen();
