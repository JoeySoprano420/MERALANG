#!/bin/bash

# Ensure dependencies
npm install

# Build VSIX package
npx vsce package

# Publish (requires Personal Access Token)
# npx vsce publish --pat $VSCE_TOKEN

echo "VSIX build complete. Run with: code --install-extension meralang-extension-1.0.0.vsix"
