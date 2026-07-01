# Third-Party Evidence

SmartContentDiet IIS Similarity Bridge does not bundle third-party source libraries, model weights, cloud services, SDK redistributables, or executable dependencies.

The bridge compiles against Unreal Engine and the public APIs of Smart Content Diet and Internal Index Service. Indexing, retrieval, vector storage, and context-pack ownership remain with Internal Index Service.

Evidence notes:

- No `Source/ThirdParty` folder is shipped in this example project.
- No vendor binaries, model weights, or external service clients are shipped by the bridge.
- Runtime prerequisites are the companion Tiny Tool Development plugins named in the README.
