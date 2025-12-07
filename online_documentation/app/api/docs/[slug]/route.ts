import { NextRequest, NextResponse } from "next/server";
import fs from "fs";
import path from "path";
import docsConfig from "../../../../docs-config.json";

export async function GET(
  request: NextRequest,
  { params }: { params: { slug: string } }
) {
  try {
    const { slug } = params;

    // Find the document configuration
    const docConfig = docsConfig.find((doc: any) => doc.endpoint === slug);

    if (!docConfig) {
      return NextResponse.json(
        { error: "Document not found" },
        { status: 404 }
      );
    }

    // Read from public/docs directory
    const filePath = path.join(
      process.cwd(),
      "public",
      "docs",
      docConfig.archivo
    );

    // Read the markdown file
    const content = fs.readFileSync(filePath, "utf-8");

    return NextResponse.json({ content });
  } catch (error) {
    console.error("Error reading markdown file:", error);
    return NextResponse.json(
      { error: "Failed to load document" },
      { status: 500 }
    );
  }
}
