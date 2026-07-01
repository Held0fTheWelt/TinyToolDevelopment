# FAQ

## What does this bridge do?

SmartContentDiet IIS Similarity Bridge lets SmartContentDiet request semantic similarity support through Internal Index Service without coupling either core plugin directly.

## Is this a standalone product?

No. It is an optional bridge package. It is useful only in projects that already use SmartContentDiet and Internal Index Service together.

## Does it replace SmartContentDiet or Internal Index Service?

No. SmartContentDiet owns asset-health review. Internal Index Service owns indexing and retrieval. This bridge only adapts similarity evidence between those products.

## Does it call AI providers directly?

No. Provider selection and embedding ownership stay with the owning index/provider stack. The bridge does not own model credentials.

## What engine versions are supported?

The bridge source targets Unreal Engine 5.4 and should be packaged and verified across the configured release matrix before publication.

## Where do I get support?

Use the support link on the Fab product page.
