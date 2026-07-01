# Third-Party Evidence

UII Internal Index Service Bridge does not bundle third-party source libraries, model weights, cloud services, SDK redistributables, or executable dependencies.

The bridge compiles against Unreal Engine and the public APIs of Unreal Integration Intelligence and Internal Index Service. UII remains the handoff/evidence owner; IIS remains the import, catalog, retrieval, context-pack, and embedding-job owner.

Evidence notes:

- No `Source/ThirdParty` folder is shipped in this example project.
- No vendor binaries, model weights, or external service clients are shipped by the bridge.
- Runtime prerequisites are the companion Tiny Tool Development plugins named in the README.
